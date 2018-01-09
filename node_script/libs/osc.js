const osc = require('node-osc');
const sender = new osc.Client('localhost', 22222);

const parseTransaction = transaction => {
    const {
        tx_index,
        inputs,
        out,
        hash,
        size,
        time
    } = transaction;
    const input_amount  = inputs.reduce((sum, x) => sum + x.prev_out.value, 0) + "";
    const output_amount = out.reduce((sum, x) => sum + x.value, 0) + "";
    return [
        time, // sec
        tx_index, 
        input_amount, 
        output_amount, 
        size 
    ];
}

module.exports = {
    transaction: (data) => {
        sender.send('/transaction', ... parseTransaction(data));
    },
    ticker: (...args) => {
        sender.send('/ticker', ...args);
    }
};
