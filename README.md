# HLS-Practice

It is a repo which contains few simple designs demonstrating the High Level Synthesis (HLS) in C/C++. The HLS tool used is Vitis HLS. The steps do perform HLS is as follows:

1. Open your VITIS HLS which comes along with Vivado installation.

2. Create a Project and Set the Part
Open your HLS environment and define the hardware constraints:
Select the FPGA Chip: You must specify the exact hardware part (e.g., Zynq, Virtex, or Arria) so the tool knows the available resources.
Set the Clock Period: Define your target frequency (e.g., 10ns for 100MHz). 

3. C-Simulation (Functional Verification)
Before you synthesize anything, you need to make sure your logic actually works.
Run C-Sim: The tool compiles your code using a standard GCC/Clang compiler.
Goal: Ensure your algorithm produces the correct results in software. If it fails here, it will definitely fail in hardware.

4. C-Synthesis 
This is where the HLS tool transforms your C++ code into Verilog or VHDL. During this phase, the tool:
Allocates Resources: Maps operations (like + or *) to hardware blocks (LUTs, DSPs).
Schedules Operations: Decides which operation happens in which clock cycle.
Binds Logic: Connects the scheduled operations to the physical FPGA fabric.

5. C/RTL Co-Simulation
Now that you have hardware code (RTL), you need to verify it against your original C++ testbench.
The tool "wraps" your Verilog/VHDL code and runs it inside a hardware simulator (like Vivado Simulator or ModelSim).
The C++ testbench feeds data into the simulator and checks if the hardware output matches the software's expected output.

6. Export the IP (Intellectual Property)
Once Co-Sim passes, you package your design.
The tool generates a .zip or .ip folder.
You can then import this block into a larger system-level tool (like Vivado IP Integrator) to connect it to a processor (like an ARM core) or memory.
