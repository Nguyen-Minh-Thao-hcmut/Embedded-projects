module read_encoder(clk, encA, encB, rst, mode, D);
	input clk, rst, encA, encB;
	input [1:0]mode;
	output [15:0]D;
	reg [15:0]D = 16'h8000;
	reg pre_encA = 0;
	reg pre_encB = 0;
	reg [1:0]mode_init = 2'b00;
	reg flag_mode = 1'b0;
	always @(posedge clk) begin
		flag_mode <= 1'b1;
		if (flag_mode == 0) begin
			mode_init <= mode;
		end
		pre_encA <= encA;
		pre_encB <= encB;
		if (rst == 1)
			D <= 16'h8000;
		else
		begin
			case (mode_init)
			2'b01:
				begin
					if ({pre_encA,encA,encB} == 2'b010)
						D <= D + 1'b1;
					else if ({pre_encA,encA,encB}==2'b011) begin
						D <= D - 1'b1;
					end
				end
			2'b10:
				begin
					if (({pre_encA,encA,encB} == 3'b010) || ({pre_encA,encA,encB} == 3'b101))
						D <= D + 1'b1;
					else if (({pre_encA,encA,encB} == 3'b011) || ({pre_encA,encA,encB} == 3'b100)) begin
						D <= D - 1'b1;
					end
				end
			2'b11:
				begin
					case ({pre_encA,encA,pre_encB,encB})
						4'b0100: D <= D + 1'b1;
						4'b1101: D <= D + 1'b1;
						4'b1011: D <= D + 1'b1;
						4'b0010: D <= D + 1'b1;
						4'b0001: D <= D - 1'b1;
						4'b0111: D <= D - 1'b1;
						4'b1110: D <= D - 1'b1;
						4'b1000: D <= D - 1'b1;
					endcase
				end
			endcase
		end
	end
endmodule
		
		

