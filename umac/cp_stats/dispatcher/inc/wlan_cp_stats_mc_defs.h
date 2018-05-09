/*
 * Copyright (c) 2012-2018 The Linux Foundation. All rights reserved.
 *
 * Previously licensed under the ISC license by Qualcomm Atheros, Inc.
 *
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * This file was originally distributed by Qualcomm Atheros, Inc.
 * under proprietary terms before Copyright ownership was assigned
 * to the Linux Foundation.
 */

/**
 * DOC: wlan_cp_stats_mc_defs.h
 *
 * This file provide definition for structure/enums/defines related to control
 * path stats componenet
 */

#ifndef __WLAN_CP_STATS_MC_DEFS_H__
#define __WLAN_CP_STATS_MC_DEFS_H__

#ifdef CONFIG_MCL

#include "wlan_cmn.h"
#include "qdf_event.h"

/**
 * enum stats_req_type - enum indicating bit position of various stats type in
 * request map
 * @TYPE_CONNECTION_TX_POWER: tx power was requested
 * @TYPE_STATION_STATS: station stats was requested
 * @TYPE_PEER_STATS: peer stats was requested
 */
enum stats_req_type {
	TYPE_CONNECTION_TX_POWER = 0,
	TYPE_STATION_STATS,
	TYPE_PEER_STATS,
	TYPE_MAX,
};

/**
 * struct wake_lock_stats - wake lock stats structure
 * @ucast_wake_up_count:        Unicast wakeup count
 * @bcast_wake_up_count:        Broadcast wakeup count
 * @ipv4_mcast_wake_up_count:   ipv4 multicast wakeup count
 * @ipv6_mcast_wake_up_count:   ipv6 multicast wakeup count
 * @ipv6_mcast_ra_stats:        ipv6 multicast ra stats
 * @ipv6_mcast_ns_stats:        ipv6 multicast ns stats
 * @ipv6_mcast_na_stats:        ipv6 multicast na stats
 * @icmpv4_count:               ipv4 icmp packet count
 * @icmpv6_count:               ipv6 icmp packet count
 * @rssi_breach_wake_up_count:  rssi breach wakeup count
 * @low_rssi_wake_up_count:     low rssi wakeup count
 * @gscan_wake_up_count:        gscan wakeup count
 * @pno_complete_wake_up_count: pno complete wakeup count
 * @pno_match_wake_up_count:    pno match wakeup count
 * @oem_response_wake_up_count: oem response wakeup count
 * @pwr_save_fail_detected:     pwr save fail detected wakeup count
 * @scan_11d                    11d scan wakeup count
 */
struct wake_lock_stats {
	uint32_t ucast_wake_up_count;
	uint32_t bcast_wake_up_count;
	uint32_t ipv4_mcast_wake_up_count;
	uint32_t ipv6_mcast_wake_up_count;
	uint32_t ipv6_mcast_ra_stats;
	uint32_t ipv6_mcast_ns_stats;
	uint32_t ipv6_mcast_na_stats;
	uint32_t icmpv4_count;
	uint32_t icmpv6_count;
	uint32_t rssi_breach_wake_up_count;
	uint32_t low_rssi_wake_up_count;
	uint32_t gscan_wake_up_count;
	uint32_t pno_complete_wake_up_count;
	uint32_t pno_match_wake_up_count;
	uint32_t oem_response_wake_up_count;
	uint32_t pwr_save_fail_detected;
	uint32_t scan_11d;
};

struct stats_event;

/**
 * struct request_info: details of each request
 * @cookie: identifier for os_if request
 * @callback: callback to process os_if request when response comes.
 * @vdev_id: vdev_id of request
 * @pdev_id: pdev_id of request
 * @peer_mac_addr: peer mac address
 */
struct request_info {
	void *cookie;
	union {
		void (*get_tx_power_cb)(int tx_power, void *cookie);
		void (*get_peer_rssi_cb)(struct stats_event *ev, void *cookie);
	} u;
	uint32_t vdev_id;
	uint32_t pdev_id;
	uint8_t peer_mac_addr[WLAN_MACADDR_LEN];
};

/**
 * struct pending_stats_requests: details of pending requests
 * @type_map: map indicating type of outstanding requests
 * @req: array of info for outstanding request of each type
 */
struct pending_stats_requests {
	uint32_t type_map;
	struct request_info req[TYPE_MAX];
};

/**
 * struct psoc_mc_cp_stats: psoc specific stats
 * @pending: details of pending requests
 * @wow_unspecified_wake_up_count: number of non-wow related wake ups
 */
struct psoc_mc_cp_stats {
	struct pending_stats_requests pending;
	uint32_t wow_unspecified_wake_up_count;
};

/**
 * struct pdev_mc_cp_stats: pdev specific stats
 * @max_pwr: max tx power for vdev
 */
struct pdev_mc_cp_stats {
	int32_t max_pwr;
};

/**
 * struct vdev_mc_cp_stats -    vdev specific stats
 * @wow_stats:                  wake_lock stats for vdev
 */
struct vdev_mc_cp_stats {
	struct wake_lock_stats wow_stats;
};

/**
 * struct peer_mc_cp_stats - peer specific stats
 * @tx_rate: tx rate
 * @rx_rate: rx rate
 * @peer_rssi: rssi
 * @peer_macaddr: mac address
 */
struct peer_mc_cp_stats {
	uint32_t tx_rate;
	uint32_t rx_rate;
	uint32_t peer_rssi;
	uint8_t peer_macaddr[WLAN_MACADDR_LEN];
};

/**
 * struct stats_event - parameters populated by stats event
 * @num_pdev_stats: num pdev stats
 * @pdev_stats: if populated array indicating pdev stats (index = pdev_id)
 * @num_peer_stats: num peer stats
 * @peer_stats: if populated array indicating peer stats
 */
struct stats_event {
	uint32_t num_pdev_stats;
	struct pdev_mc_cp_stats *pdev_stats;
	uint32_t num_peer_stats;
	struct peer_mc_cp_stats *peer_stats;
};

#endif /* CONFIG_MCL */
#endif /* __WLAN_CP_STATS_MC_DEFS_H__ */
