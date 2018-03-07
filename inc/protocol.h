/*
 * protocol.h
 *
 *  Created on: Mar 6, 2018
 *      Author: dipsy
 */

#ifndef INC_PROTOCOL_H_
#define INC_PROTOCOL_H_

#include <string>

#include "bluetooth.h"
#include "product.h"

class Protocol{
public:


	Bluetooth m_bt;

	uint8_t ip[4];
	vector<Product> products;
	uint8_t products_count=0;
	uint32_t timestamp = 0;
	bool purchase_result = 0;

	bool ip_ready = false;
	bool products_ready = false;
	bool purchase_ready = false;

	bool waiting_ip = false;
	bool waiting_products = false;
	bool waiting_purchase = false;

	Protocol():m_bt(0,1){
		memset(ip,0,4);
		m_bt.SetCustomHandler([&](const Bluetooth::Package& pkg){
			this->Handler(pkg);
		});
	}

	/**
	 * Return 0 means submit request fail,
	 * probably previous same request have not received
	 */
	bool RequestIp();
	bool RequestProducts();
	bool RequestPurchase(uint16_t card_id, uint8_t product_id, uint32_t checksum);

	void Handler(const Bluetooth::Package& pkg);
	void IpHandler(const Bluetooth::Package& pkg);
	void ProductsHandler(const Bluetooth::Package& pkg);
	void PurchaseHandler(const Bluetooth::Package& pkg);

	void CancelAwait();

	/**
	 * halt program until ip is ready and return requested ip
	 */
	std::string AwaitRequestIp();

	/**
	 * halt program until product list is ready and return requested list
	 */
	vector<Product>& AwaitRequestProducts();

	/**
	 * halt program until purchase result is ready and return request result
	 */
	bool AwaitRequestPurchase();

private:
	bool cancel_await = false;
};



#endif /* INC_PROTOCOL_H_ */