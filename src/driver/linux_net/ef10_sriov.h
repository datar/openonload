/*
** Copyright 2005-2016  Solarflare Communications Inc.
**                      7505 Irvine Center Drive, Irvine, CA 92618, USA
** Copyright 2002-2005  Level 5 Networks Inc.
**
** This program is free software; you can redistribute it and/or modify it
** under the terms of version 2 of the GNU General Public License as
** published by the Free Software Foundation.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
*/

/****************************************************************************
 * Driver for Solarflare network controllers and boards
 * Copyright 2014-2015 Solarflare Communications Inc.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#ifndef EF10_SRIOV_H
#define EF10_SRIOV_H

#include "net_driver.h"

/**
 * struct ef10_vf - PF's store of VF data
 * @efx: efx_nic struct for the current VF
 * @pci_dev: the pci_dev struct for the VF, retained while the VF is assigned
 * @vport_id: vport ID for the VF
 * @vport_assigned: record whether the vport is currently assigned to the VF
 * @mac: MAC address for the VF, zero when address is removed from the vport
 * @vlan: Default VLAN for the VF or #EFX_EF10_NO_VLAN
 */
struct ef10_vf {
	struct efx_nic *efx;
	struct pci_dev *pci_dev;
	unsigned int vport_id;
	unsigned int vport_assigned;
	u8 mac[ETH_ALEN];
	u16 vlan;
#define EFX_EF10_NO_VLAN	0
};

int efx_ef10_sriov_init(struct efx_nic *efx);
void efx_ef10_sriov_fini(struct efx_nic *efx);
bool efx_ef10_sriov_wanted(struct efx_nic *efx);
int efx_ef10_sriov_configure(struct efx_nic *efx, int num_vfs);
void efx_ef10_sriov_flr(struct efx_nic *efx, unsigned flr);

int efx_ef10_vswitching_probe_pf(struct efx_nic *efx);
int efx_ef10_vswitching_probe_vf(struct efx_nic *efx);
int efx_ef10_vswitching_restore_pf(struct efx_nic *efx);
int efx_ef10_vswitching_restore_vf(struct efx_nic *efx);
void efx_ef10_vswitching_remove_pf(struct efx_nic *efx);
void efx_ef10_vswitching_remove_vf(struct efx_nic *efx);
int efx_ef10_vadaptor_alloc(struct efx_nic *efx, unsigned int port_id);
int efx_ef10_vadaptor_free(struct efx_nic *efx, unsigned int port_id);

int efx_ef10_sriov_set_vf_mac(struct efx_nic *efx, int vf_i, u8 *mac);
int efx_ef10_sriov_set_vf_vlan(struct efx_nic *efx, int vf_i, u16 vlan,
			       u8 qos);
int efx_ef10_sriov_set_vf_spoofchk(struct efx_nic *efx, int vf, bool spoofchk);
#if !defined(EFX_USE_KCOMPAT) || defined(EFX_HAVE_NDO_SET_VF_MAC)
int efx_ef10_sriov_get_vf_config(struct efx_nic *efx, int vf_i,
				 struct ifla_vf_info *ivf);
#ifdef EFX_HAVE_VF_LINK_STATE
int efx_ef10_sriov_set_vf_link_state(struct efx_nic *efx, int vf_i,
				     int link_state);
#endif
#endif

/* MCFW vswitch operations */
int efx_ef10_vswitch_alloc(struct efx_nic *efx, unsigned int port_id,
			   unsigned int vswitch_type);
int efx_ef10_vswitch_free(struct efx_nic *efx, unsigned int port_id);
int efx_ef10_vport_alloc(struct efx_nic *efx, unsigned int port_id_in,
			 unsigned int vport_type, u16 vlan,
			 unsigned int *port_id_out);
int efx_ef10_vport_free(struct efx_nic *efx, unsigned int port_id);
int efx_ef10_evb_port_assign(struct efx_nic *efx, unsigned int port_id,
			     unsigned int vf_fn);
int efx_ef10_vport_add_mac(struct efx_nic *efx, unsigned int port_id, u8 *mac);
int efx_ef10_vport_del_mac(struct efx_nic *efx, unsigned int port_id, u8 *mac);

#endif /* EF10_SRIOV_H */
