// ***************************
// Date:
// Author:
// Module Name: ALU
// Description:
// ***************************
//


module ALU #(parameter WIDTH = 32)
            (input  logic [WIDTH-1:0] i_a,
             input  logic [WIDTH-1:0] i_b,
             input  logic [2:0]       i_alucontrol,
             output logic [WIDTH-1:0] o_result,
             output logic             o_zero);

  logic [WIDTH-1:0] b2, andresult, orresult, sumresult, sltresult;

    assign andresult = i_a & i_b;
    assign orresult = i_a | i_b;
    // Conditional Inverse
    always_comb begin
        case(i_alucontrol[2])
            1'b1: b2 = ~i_b;
            1'b0: b2 = i_b;
        endcase
    end
    always_comb
/* verilator lint_off WIDTH */
// Sim tool likes explicit bit padding, but it is error prone and unecesarily verbose
        sumresult = i_a + b2 + i_alucontrol[2];
  // slt should be 1 if most significant bit of sum is 1
    assign sltresult = sumresult[WIDTH-1];
/* verilator lint_on WIDTH */

    always_comb
        case(i_alucontrol[1:0])
            2'b00: o_result = orresult;
            2'b01: o_result = andresult;
            2'b10: o_result = sumresult;
            2'b11: o_result = sltresult;
        endcase

  assign o_zero = (o_result==0);
endmodule


