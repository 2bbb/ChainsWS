# Data format

## ticker.csv

* timestamp
* name
  * currency name
* last
  * last price (/btc)
* b15m
  * price before 15m (/btc)
* buy
  * lowest price for buy (/btc)
* sell
  * highest price for sell (/btc)

## tx_meta.csv

* tx_id
  * transaction id
* timestamp
* vin_sz
  * input num
* vout_sz
  * output num

## tx_in.csv

* tx_id
  * transaction id
* p_tx_id
  * previous transaction id
* addr
  * bitcoin address sent from
* value
  * sent value (satoshi = 10^-8btc)

## tx_out.csv

* tx_id
  * transaction id
* addr
  - bitcoin address sent to
* value
  - sent value (satoshi = 10^-8btc)