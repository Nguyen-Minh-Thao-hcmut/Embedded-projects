module HK1_1718(clk,PULSEIN,MODE,D);
input clk, PULSEIN;
input [1:0]MODE;
output [15:0]D;
reg [15:0]D = 16'h0000;
reg [15:0]tmp = 16'h0000;
reg pulse_cnt = 2'h0;
reg pre_pulse = 0;
	initial pulse_cnt = MODE;
	always @(posedge clk) begin
		pre_pulse <= PULSEIN;
		case ({pre_pulse, PULSEIN}) 
			2'b01:
			begin
				tmp <= 0;
				if (pulse_cnt == 0) begin
					D <= tmp; pulse_cnt <= MODE;
				end
			end
			2'b10: 
			begin
				pulse_cnt <= pulse_cnt - 1;
				tmp <= tmp + 1;
			end
			default: tmp <= tmp + 1;
		endcase
	end
endmodule
	
	