#ifndef __VG_SL_TransferDatas_H_INCLUDE__
#define __VG_SL_TransferDatas_H_INCLUDE__
#include "ConfigForSL.h"
#include "vgArray.h"
#include "vg_PerVertex.h"
#include "SDataFSOut.h"
#include "SDataGSOut.h"
#include "SDataVSOut.h"
#include "SDataPAOut.h"
#include "TDataBag.h"
#include "SDataRasiOut.h"
#include "SSLMachineStatus.h"

//
#include "SDataFSInner.h"
#include "SDataGSInner.h"
#include "SDataPAInner.h"
#include "SDataVSInner.h"

namespace vg
{
	namespace sl
	{
		struct TransferDatas
		{
			//vs->prim
			SDataVSOut* DataVstoPA;
			//prim->gs
			SDataPAOut* DataPAtoGS;
			//gs->rasi
			SDataGSOut* DataGstoRasi;
			//rasi->fs
			SDataRasiOut* DataRasitoFS;
			//fs->perfraghandle
			SDataFSOut* DataFstoPerFS;

			//status machine
			SSLMachineStatus* MachineStatus;
			
			TransferDatas()
			{
				DataVstoPA = new SDataVSOut();
				DataPAtoGS = new SDataPAOut();
				DataFstoPerFS = new SDataFSOut();
				DataGstoRasi = new SDataGSOut();
				DataRasitoFS = new SDataRasiOut();
				MachineStatus = new SSLMachineStatus();
			}

			~TransferDatas()
			{
				if (DataVstoPA)
					delete DataVstoPA;
				if (DataPAtoGS)
					delete DataPAtoGS;
				if (DataFstoPerFS)
					delete DataFstoPerFS;
				if (DataGstoRasi)
					delete DataGstoRasi;
				if (DataRasitoFS)
					delete DataRasitoFS;
				if (MachineStatus)
					delete MachineStatus;
			}

			void resetAll()
			{
				if (DataVstoPA)
					DataVstoPA->reset();
				if (DataPAtoGS)
					DataPAtoGS->reset();
				if (DataFstoPerFS)
					DataFstoPerFS->reset();
				if (DataGstoRasi)
					DataGstoRasi->reset();
				if (DataRasitoFS)
					DataRasitoFS->reset();
				if (MachineStatus)
					MachineStatus->reset();
			}

		};
	}
}
#endif//! __VG_SL_SDATAVSOUT_H_INCLUDE__