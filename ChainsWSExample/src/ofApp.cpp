#include "ofMain.h"

#include "ofxPubSubOsc.h"
#include "ofxZmq.h"

#include "Blockchain.h"

static constexpr std::size_t num_transaction = 50;

struct Transaction : public Blockchain::SimpleTransaction {
    Transaction(std::uint64_t time, std::uint64_t tx_id, double input, double output, std::size_t size)
        : Blockchain::SimpleTransaction(time, tx_id, input, output, size)
        , x(ofRandomWidth())
        , y(ofRandomHeight())
        , age(255)
        , size(log(output * 0.00001 + 2) * 10)
    {};
    
    void draw() {
        ofSetColor(255, 0, 0, age);
        ofDrawCircle(x, y, size);
        ofSetColor(255, 255, 255, age);
        ofDrawBitmapString(ofToString(tx_id), x + size, y + 0.5f * size);
        ofDrawBitmapString(ofToString(output), x + size, y + 0.5f * size + 24);
        age--;
    };
    
    float x;
    float y;
    int age;
    float size;
};

class ofApp : public ofBaseApp {
    std::deque<Blockchain::Block> blocks;
    std::deque<Transaction> transactions;
    std::map<std::string, Blockchain::Ticker> tickers;
    
    ofxZmqSubscriber subscriber;
    
public:
    void setup() {
        ofJson setting = ofLoadJson("setting.json");
        
        ofJson osc_setting = setting["osc"];
        std::uint16_t osc_port = osc_setting["port"];
        
        ofxSubscribeOsc(osc_port, "/transaction", [=](std::uint64_t time, std::uint64_t tx_id, double input, double output, std::size_t size) {
            transactions.emplace_back(time, tx_id, input, output, size);
        });
        ofxSubscribeOsc(osc_port, "/ticker", [=](const std::string &key, double buy, double sell, double last, double before15m) {
            tickers[key].key       = key;
            tickers[key].buy       = buy;
            tickers[key].sell      = sell;
            tickers[key].last      = last;
            tickers[key].before15m = before15m;
        });
        ofSetBackgroundColor(0, 0, 0);
        ofSetColor(255, 255, 255);
        
        ofJson zmq_setting = setting["zmq"];
        std::string zmq_host = zmq_setting["host"];
        std::uint16_t zmq_port = zmq_setting["port"];
        std::string zmq_destination = "tcp://" + zmq_host + ":" + ofToString(zmq_port);
        subscriber.connect(zmq_destination);
        
        ofSetCircleResolution(64);
    }
    void update() {
//        if(num_transaction < transactions.size()) {
//            transactions.erase(transactions.begin(), transactions.begin() + transactions.size() - num_transaction);
//        }
        auto it = std::remove_if(transactions.begin(), transactions.end(), [](const Transaction &t) {
            return t.age == 0;
        });
        transactions.erase(it, transactions.end());
        
        while(subscriber.hasWaitingMessage()) {
            std::string data;
            subscriber.getNextMessage(data);
            ofLogNotice() << data;
            blocks.emplace_back();
            ofJson json = ofxJsonUtils::parse(data);
            ofxJsonUtils::parse(json, blocks.back());
        }
    }
    void draw() {
        for(auto &&tx : transactions) {
            tx.draw();
        }
        
        ofSetColor(255, 255, 255);
        std::size_t i = 0;
        for(; i < transactions.size(); i++) {
            ofDrawBitmapString(transactions[i].print(), 20, 20 + i * 24);
        }
        i = 0;
        if(blocks.size()) {
            const auto &block = blocks.back();
            ofDrawBitmapString("time:         " + ofToString(block.time), 640, 20 + 24 * i++);
            ofDrawBitmapString("transactions: " + ofToString(block.txIndexes.size()), 640, 20 + 24 * i++);
            ofDrawBitmapString("hash:         " + block.hash, 640, 20 + 24 * i++);
            ofDrawBitmapString("estimated BTC sent: " + ofToString(block.estimatedBTCSent), 640, 20 + 24 * i++);
            ofDrawBitmapString("total BTC sent:     " + ofToString(block.totalBTCSent), 640, 20 + 24 * i++);
        }
        i = 6;
        for(auto &&pair : tickers) {
            auto &&ticker = pair.second;
            std::string &&str = ofVAArgsToString("%s : %12.2f / %12.2f / %12.2f", ticker.key.c_str(), ticker.last, ticker.buy, ticker.sell);
            ofDrawBitmapString(str, 640, 20 + i++ * 24);
        }
    }
    void exit() {}
    
    void keyPressed(int key) {
        if(key == 'F') {
            ofToggleFullscreen();
        }
    }
    void keyReleased(int key) {}
    void mouseMoved(int x, int y ) {}
    void mouseDragged(int x, int y, int button) {}
    void mousePressed(int x, int y, int button) {}
    void mouseReleased(int x, int y, int button) {}
    void mouseEntered(int x, int y) {}
    void mouseExited(int x, int y) {}
    void windowResized(int w, int h) {}
    void dragEvent(ofDragInfo dragInfo) {}
    void gotMessage(ofMessage msg) {}
};

int main() {
    ofSetupOpenGL(1280, 720, OF_WINDOW);
    ofRunApp(new ofApp());
}
