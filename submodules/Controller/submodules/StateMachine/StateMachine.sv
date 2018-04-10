// ***************************
// Date:
// Author:
// Module Name: StateMachine
// Description:
// ***************************

module StateMachine(
    input logic         i_clk,
    input logic         i_reset,
    input logic [5:0]   i_op,
    // output logic        o_memread,
    output logic        o_memwrite,
    output logic        o_alusrca,
    output logic        o_memtoreg,
    output logic        o_instrwrite,
    output logic        o_iord,
    output logic        o_pcwrite,
    output logic        o_regwrite,
    output logic        o_regdst,
    output logic        o_branch,
    output logic [1:0]  o_pcsrc,
    output logic [1:0]  o_alusrcb,
    output logic [1:0]  o_aluop);

// INTERNAL VARIABLES ********
typedef enum logic [3:0] {S_RESET = 4'b0000,
                          S_FETCH,
                          S_DECODE,
                          S_MEMADR,
                          S_LBRD,
                          S_LBWR,
                          S_SBWR,
                          S_RTYPEEX,
                          S_RTYPEWR,
                          S_BEQEX,
                          S_JEX} statetype;
statetype state, nextstate;

typedef enum logic [5:0] {LB    = 6'b100000,
                          SB    = 6'b101000,
                          RTYPE = 6'b000000,
                          BEQ   = 6'b000100,
                          J     = 6'b000010} opcode;

// MODULE START***************
always_ff @(posedge i_clk)
    if(i_reset) begin
        state <= S_RESET;
    end
    else begin
        state <= nextstate;
    end

always_comb begin
    // Default outputs
    // o_memread    = 'b0;
    o_memwrite   = 'b0;
    o_alusrca    = 'b0;
    o_memtoreg   = 'b0;
    o_instrwrite = 'b0;
    o_iord       = 'b0;
    o_pcwrite    = 'b0;
    o_regwrite   = 'b0;
    o_regdst     = 'b0;
    o_branch     = 'b0;
    o_pcsrc      = 'b0;
    o_alusrcb    = 'b0;
    o_aluop      = 'b0;
    case (state)
        S_RESET: begin
            o_pcwrite = 1'b1;
            o_instrwrite = 1'b1;
            o_alusrcb = 2'b01;
            if(i_reset)
                nextstate = S_RESET;
            else begin
                nextstate = S_DECODE;
            end
        end
        S_FETCH: begin
            o_pcwrite = 1'b1;
            o_instrwrite = 1'b1;
            o_alusrcb = 2'b01;
            nextstate = S_DECODE;
        end
        S_DECODE: begin
            o_alusrcb = 2'b11;
            case (i_op)
                LB:     nextstate = S_MEMADR;
                SB:     nextstate = S_MEMADR;
                RTYPE:  nextstate = S_RTYPEEX;
                BEQ:    nextstate = S_BEQEX;
                J:      nextstate = S_JEX;
                default:    nextstate = S_FETCH;
            endcase
        end
        S_MEMADR: begin
            o_alusrca = 1'b1;
            o_alusrcb = 2'b10;
            case (i_op)
                LB:     nextstate = S_LBRD;
                SB:     nextstate = S_SBWR;
                default:    nextstate = S_FETCH;
            endcase
        end
        S_RTYPEEX: begin
            o_alusrca = 1'b1;
            o_aluop = 2'b10;
            nextstate = S_RTYPEWR;
        end
        S_BEQEX: begin
            o_alusrca = 1'b1;
            o_pcsrc = 2'b01;
            o_aluop = 2'b01;
            o_branch = 1'b1;
            nextstate = S_FETCH;
        end
        S_JEX: begin
            o_pcwrite = 1'b1;
            o_pcsrc = 2'b10;
            nextstate = S_FETCH;
        end
        S_LBRD: begin
            o_iord = 1'b1;
            nextstate = S_LBWR;
        end
        S_SBWR: begin
            o_memwrite = 1'b1;
            o_iord = 1'b1;
            nextstate = S_FETCH;
        end
        S_RTYPEWR: begin
            o_regwrite = 1'b1;
            o_regdst = 1'b1;
            nextstate = S_FETCH;
        end
        S_LBWR: begin
            // o_iord = 1'b1;
            o_memtoreg = 1'b1;
            o_regwrite = 1'b1;
            nextstate = S_FETCH;
        end
        default:    nextstate = S_FETCH;
    endcase
end

endmodule
