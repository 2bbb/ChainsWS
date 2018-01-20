const blockchaininfo = require('blockchain.info');
const {Socket, statistics, blockexplorer, exchange} = blockchaininfo;

const osc = require('./libs/osc.js');
const zmq = require('./libs/zmq.js');

const socket = new Socket();

function startSocket() {
    socket.onOpen(() => {
        console.log('open at', new Date());
    });

    socket.onClose(() => {
        console.log('close at', new Date());
        startSocket();
    });

    socket.onTransaction(data => {
        // console.log('tx:', JSON.stringify(data, null, "  "));
        osc.transaction(data);
    });

    socket.onBlock(data => {
// console.log("block:", data);
        zmq.block(data);
    });
}

const double = value => ({type: 'double', value});

function getTicker() {
    exchange
        .getTicker()
        .then(data => {
            for(let key in data) {
                const tick = data[key];
                console.log(tick);
                osc.ticker(key, double(tick.buy), double(tick.sell), double(tick.last), double(tick['15m']));
            }
        })
        .catch(err => {
            console.error(err);
        });
}

startSocket();
setInterval(getTicker, 10000);
getTicker();
