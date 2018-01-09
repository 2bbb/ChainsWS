const blockchaininfo = require('blockchain.info');
const {Socket, statistics, blockexplorer, exchange} = blockchaininfo;

const osc = require('./libs/osc.js');
const zmq = require('./libs/zmq.js');

const socket = new Socket();

socket.onOpen(() => {
    console.log('open at', new Date());
});

socket.onClose(() => {
    console.log('close at', new Date());
});

socket.onTransaction(data => {
    osc.transaction(data);
});

socket.onBlock(data => {
    zmq.block(data);
});

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

setInterval(getTicker, 6000);
getTicker();
