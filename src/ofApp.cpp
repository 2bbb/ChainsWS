#include "ofMain.h"

#include "ofxPubSubOsc.h"
#include "ofxZmq.h"

#include "Blockchain.h"

static constexpr std::uint16_t osc_port = 22222;
static constexpr std::size_t num_transaction = 30;

struct Ticker {
    std::string key;
    std::uint64_t buy;
    std::uint64_t sell;
    std::uint64_t last;
    std::uint64_t before15m;
};

class ofApp : public ofBaseApp {
    std::deque<std::string> transactions;
    std::deque<Blockchain::Block> blocks;
    std::map<std::string, Ticker> tickers;
    ofxZmqSubscriber subscriber;
public:
    void setup() {
        ofxSubscribeOsc(osc_port, "/transaction", [=](std::uint64_t time, std::uint64_t tx_id, std::string input, std::string output, std::size_t size) {
            std::string str = ofVAArgsToString("%8d [at %8d] %12s : %12s / %6d", tx_id, time, input.c_str(), output.c_str(), size);
            transactions.emplace_back(str);
        });
        ofxSubscribeOsc(osc_port, "/ticker", [=](const std::string &key, const std::string &buy, const std::string &sell, const std::string &last, const std::string &before15m) {
            tickers[key].key       = key;
            tickers[key].buy       = std::stoull(buy);
            tickers[key].sell      = std::stoull(sell);
            tickers[key].last      = std::stoull(last);
            tickers[key].before15m = std::stoull(before15m);
        });
        ofSetBackgroundColor(0, 0, 0);
        ofSetColor(255, 255, 255);
        subscriber.connect("tcp://localhost:22223");
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
        std::size_t i = 0;
        for(; i < transactions.size(); i++) {
            ofDrawBitmapString(transactions[i], 20, 20 + i * 24);
        }
        i = 0;
        if(blocks.size()) {
            const auto &block = blocks.back();
            ofDrawBitmapString("time:         " + ofToString(block.time), 640, 20 + 24 * i++);
            ofDrawBitmapString("transactions: " + ofToString(block.txIndexes.size()), 640, 20 + 24 * i++);
            ofDrawBitmapString("hash:         " + block.hash, 640, 20 + 24 * i++);
            ofDrawBitmapString("est BTC sent: " + ofToString(block.estimatedBTCSent), 640, 20 + 24 * i++);
            ofDrawBitmapString("total sent:   " + ofToString(block.totalBTCSent), 640, 20 + 24 * i++);
        }
        i = 6;
        for(auto &&pair : tickers) {
            auto &&ticker = pair.second;
            std::string &&str = ofVAArgsToString("%s : %8d / %8d / %8d", ticker.key.c_str(), ticker.last, ticker.buy, ticker.sell);
//            std::stringstream ss;
//            ss << ticker.key << " : " << ticker.last << " / " << ticker.buy << " / " << ticker.sell;
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
