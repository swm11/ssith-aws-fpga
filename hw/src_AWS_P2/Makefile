CONNECTALDIR ?= ../connectal

FLUTE_DIR ?= ../Flute

############################################################
## Connectal topgen configuration
############################################################

S2H_INTERFACES = AWSP2_Request:AWSP2.request
H2S_INTERFACES = AWSP2:AWSP2_Response
MEM_READ_INTERFACES = lAWSP2.readClients
MEM_WRITE_INTERFACES = lAWSP2.writeClients

ifeq ($(BOARD),awsf1)
PIN_TYPE=AWSP2_Pin_IFC
PIN_TYPE_INCLUDE=AWSP2_IFC
AUTOTOP = --interface pins:AWSP2.pins
endif

BSVFILES = ../src_BSV/AWSP2_IFC.bsv

############################################################
## the software source code and compiler flags
############################################################

CPPFILES = ../src_Software/loadelf.cpp ../src_Software/testawsp2.cpp
CONNECTALFLAGS += -lelf


############################################################
## Configuring connectal platform hardware
############################################################

CONNECTALFLAGS += -D SIM_DMA_READ_LATENCY=1
CONNECTALFLAGS += -D SIM_DMA_WRITE_LATENCY=1

CONNECTALFLAGS += -D BYTE_ENABLES_MEM_DATA
CONNECTALFLAGS += -D DataBusWidth=512
CONNECTALFLAGS += -D AWSF1_CL_DEBUG_BRIDGE

CONNECTALFLAGS += -D AWSF1_DDR_A
CONNECTALFLAGS += -D AWSF1_DMA_PCIS

############################################################
## copied from src_SSITH_P2 Makefile
############################################################

ARCH ?= RV64ACDFIMSU

BSCFLAGS += \
	-keep-fires -aggressive-conditions -no-warn-action-shadowing -no-show-timestamps \
	-suppress-warnings G0020    \
	+RTS -K128M -RTS  -show-range-conflict

CONNECTALFLAGS += --bscflags="$(BSCFLAGS)"
CONNECTALFLAGS += -DRV64
CONNECTALFLAGS += -DSV39
CONNECTALFLAGS += -DISA_PRIV_M  -DISA_PRIV_S  -DISA_PRIV_U
CONNECTALFLAGS += -DISA_I  -DISA_M  -DISA_A  -DISA_C
CONNECTALFLAGS += -DISA_F -DISA_D -DISA_FD_DIV
CONNECTALFLAGS += -DISA_FD -DISA_F_OR_D
CONNECTALFLAGS += -DSHIFT_BARREL
CONNECTALFLAGS += -DMULT_SERIAL
CONNECTALFLAGS += -DNear_Mem_Caches
CONNECTALFLAGS += -DFABRIC64
CONNECTALFLAGS += -DINCLUDE_GDB_CONTROL
CONNECTALFLAGS += -DINCLUDE_TANDEM_VERIF
CONNECTALFLAGS += -DBRVF_TRACE
CONNECTALFLAGS += -DXILINX_BSCAN  -DXILINX_XCVU9P
CONNECTALFLAGS += -DVERILATOR_PROJECT_ARGS=--trace

## this design uses the DMI interface directly
#CONNECTALFLAGS += -DJTAG_TAP

CONNECTALFLAGS += --bsvpath=../src_BSV
## CONNECTALFLAGS += --bsvpath=$(FLUTE_DIR)/src_SSITH_P2/src_BSV/
CONNECTALFLAGS += --bsvpath=$(FLUTE_DIR)/src_Core/BSV_Additional_Libs
CONNECTALFLAGS += --bsvpath=$(FLUTE_DIR)/src_Core/Core
CONNECTALFLAGS += --bsvpath=$(FLUTE_DIR)/src_Core/CPU
CONNECTALFLAGS += --bsvpath=$(FLUTE_DIR)/src_Core/Debug_Module
CONNECTALFLAGS += --bsvpath=$(FLUTE_DIR)/src_Core/ISA
CONNECTALFLAGS += --bsvpath=$(FLUTE_DIR)/src_Core/Near_Mem_IO
CONNECTALFLAGS += --bsvpath=$(FLUTE_DIR)/src_Core/Near_Mem_VM
CONNECTALFLAGS += --bsvpath=$(FLUTE_DIR)/src_Core/PLIC
CONNECTALFLAGS += --bsvpath=$(FLUTE_DIR)/src_Core/RegFiles
CONNECTALFLAGS += --bsvpath=$(FLUTE_DIR)/src_Testbench/Fabrics/AXI4
CONNECTALFLAGS += --bsvpath=$(FLUTE_DIR)/src_Testbench/SoC

## for TLM.defines
CONNECTALFLAGS += $(shell test -d $(BLUESPECDIR)/Libraries/Axi && echo --bsvpath=$(BLUESPECDIR)/Libraries/Axi)
CONNECTALFLAGS += $(shell test -d $(BLUESPECDIR)/Libraries/Axi4 && echo --bsvpath=$(BLUESPECDIR)/Libraries/Axi4)
CONNECTALFLAGS += $(shell test -d $(BLUESPECDIR)/Libraries/Bus && echo --bsvpath=$(BLUESPECDIR)/Libraries/Bus)
CONNECTALFLAGS += $(shell test -d $(BLUESPECDIR)/Libraries/TLM3 && echo --bsvpath=$(BLUESPECDIR)/Libraries/TLM3)
CONNECTALFLAGS += $(shell test -d $(BLUESPECDIR)/Libraries/AMBA_TLM3/Axi && echo --bsvpath=$(BLUESPECDIR)/Libraries/AMBA_TLM3/Axi)
CONNECTALFLAGS += $(shell test -d $(BLUESPECDIR)/Libraries/AMBA_TLM3/Axi4 && echo --bsvpath=$(BLUESPECDIR)/Libraries/AMBA_TLM3/Axi4)
CONNECTALFLAGS += $(shell test -d $(BLUESPECDIR)/Libraries/AMBA_TLM3/TLM3 && echo --bsvpath=$(BLUESPECDIR)/Libraries/AMBA_TLM3/TLM3)

ifeq ($(BOARD),awsf1)

prebuild:: $(CONNECTALDIR)/out/awsf1/ila_connectal_1/ila_connectal_1.xci

$(CONNECTALDIR)/out/awsf1/ila_connectal_1/ila_connectal_1.xci:
	cd awsf1; vivado -mode batch -source $(CONNECTALDIR)/scripts/connectal-synth-ila.tcl
endif

include $(CONNECTALDIR)/Makefile.connectal
