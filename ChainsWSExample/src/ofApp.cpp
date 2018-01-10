#include "ofMain.h"

#include "ofxPubSubOsc.h"
#include "ofxZmq.h"

#include "Blockchain.h"

static constexpr std::uint16_t osc_port = 22222;
static constexpr std::size_t num_transaction = 30;

struct Transaction : public Blockchain::SimpleTransaction {
    Transaction(std::uint64_t time, std::uint64_t tx_id, double input, double output, std::size_t size)
        : Blockchain::SimpleTransaction(time, tx_id, input, output, size)
        , x(ofRandomWidth())
        , y(ofRandomHeight())
    {};
    
    void draw() const {
        ofSetColor(255, 0, 0, 127);
        ofDrawCircle(x, y, output * 0.0000001);
    };
    
    float x;
    float y;
};

class ofApp : public ofBaseApp {
    std::deque<Blockchain::Block> blocks;
    std::deque<Transaction> transactions;
    std::map<std::string, Blockchain::Ticker> tickers;
    
    ofxZmqSubscriber subscriber;
    
public:
    void setup() {
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
        subscriber.connect("tcp://localhost:22223");
        
        ofSetCircleResolution(64);
    }
    void update() {
        if(num_transaction < transactions.size()) {
            transactions.erase(transactions.begin(), transactions.begin() + transactions.size() - num_transaction);
        }
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
    
    void keyPressed(int key) {}
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
