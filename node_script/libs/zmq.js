const zmq = require('zmq');
const pub = zmq.socket('pub');
pub.bindSync('tcp://*:22223');

module.exports = {
    block(data) {
        pub.send(JSON.stringify(data));
    }
};
