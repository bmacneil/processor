// ***************************
// Date:
// Author:
// Module Name: Processor
// Description:
// ***************************
`include "submodules/Datapath/Datapath.sv"
`include "submodules/Controller/Controller.sv"


module Processor #(parameter WIDTH = 32) (
    input logic                i_clk,
    input logic                i_reset,
    input logic [WIDTH-1:0]    i_ReadData,
    output logic               o_memwrite,
    output logic [WIDTH-1:0]   o_WriteData,
    output logic [WIDTH-1:0]   o_Address);

// INTERNAL VARIABLES ********

    logic       zero;
    logic [5:0] funct;
    logic [5:0] op;
    // logic       memread; // Not sure of the function of this
    logic       alusrca;
    logic       memtoreg;
    logic       instrwrite;
    logic       pcen;
    logic       regwrite;
    logic       regdst;
    logic       iord;
    logic [1:0] pcsrc;
    logic [1:0] alusrcb;
    logic [2:0] alucontrol;

// SUB MODULE ***************
Datapath datapath_0 (
    .i_clk          ( i_clk ),  // Size []
    .i_reset        ( i_reset ),  // Size []
    .i_regwrite     ( regwrite ),  // Size []
    .i_memtoreg     ( memtoreg ),  // Size []
    .i_regdst       ( regdst ),  // Size []
    .i_instrwrite   ( instrwrite ),  // Size []
    .i_PCen         ( pcen ),  // Size []
    .i_IorD         ( iord ),  // Size []
    .i_AluSrcA      ( alusrca ),  // Size []
    .i_PCsrc        ( pcsrc ),  // Size [1, 0]
    .i_AluSrcB      ( alusrcb ),  // Size [1, 0]
    .i_alucontrol   ( alucontrol ),  // Size [2, 0]
    .i_Memdata      ( i_ReadData ),  // Size [31, 0]
    .o_op           ( op ),  // Size [5, 0]
    .o_funct        ( funct ),  // Size [5, 0]
    .o_zero         ( zero ),  // Size []
    .o_WriteData    ( o_WriteData ),  // Size [31, 0]
    .o_Address      ( o_Address )  // Size [31, 0]
);

// ******************************
Controller controller_0 (
    .i_clk          ( i_clk ),  // Size []
    .i_reset        ( i_reset ),  // Size []
    .i_zero         ( zero ),  // Size []
    .i_funct        ( funct ),  // Size [5, 0]
    .i_op           ( op ),  // Size [5, 0]
    // .o_memread      ( memread ),  // Size []
    .o_memwrite     ( o_memwrite ),  // Size []
    .o_alusrca      ( alusrca ),  // Size []
    .o_memtoreg     ( memtoreg ),  // Size []
    .o_instrwrite   ( instrwrite ),  // Size []
    .o_pcen         ( pcen ),  // Size []
    .o_regwrite     ( regwrite ),  // Size []
    .o_regdst       ( regdst ),  // Size []
    .o_iord         ( iord ),  // Size []
    .o_pcsrc        ( pcsrc ),  // Size [1, 0]
    .o_alusrcb      ( alusrcb ),  // Size [1, 0]
    .o_alucontrol   ( alucontrol )  // Size [2, 0]
);

// MODULE START***************

endmodule // Processor