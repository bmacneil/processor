// ***************************
// Date:
// Author:
// Module Name: PCdec
// Description:
// ***************************

module PCdec #(parameter WIDTH = 32 ) (
    input logic                i_clk,
    input logic                i_reset,
    input logic                i_PCen,
    input logic                i_IorD,
    input logic [1:0]          i_PCsrc,
    input logic [WIDTH-1:0]    i_ALUresult,
    input logic [WIDTH-1:0]    i_Imm,
    output logic [WIDTH-1:0]   o_Address,
    output logic [WIDTH-1:0]   o_ALUout,
    output logic [WIDTH-1:0]   o_PC);

// INTERNAL VARIABLES ********
logic [WIDTH-1:0] ALU_sig;

// MODULE START***************

always_ff @(posedge i_clk) begin
    if(i_reset) begin
        ALU_sig <= 'b0;
    end
    else begin
        ALU_sig <= i_ALUresult;
    end
end


always_ff @(posedge i_clk) begin
    if(i_reset) begin
        // Reset State
        o_PC <= 'b0;
    end
    else begin
        if(i_PCen) begin
            case (i_PCsrc)
                2'b01 : o_PC <= ALU_sig;
                2'b10 : o_PC <= i_Imm;
                default : o_PC <= i_ALUresult;
            endcase
        end
    end
end

assign o_Address = i_IorD ? ALU_sig : o_PC;
assign o_ALUout = ALU_sig;

endmodule // PCdec