main: main.cpp GainAdjustment.o GainAdjustment.h LowPassFilter.o LowPassFilter.h AudioModule.o AudioModule.h
	g++ -o AudioProcessor.exe main.cpp GainAdjustment.o
GainAdjustment.o: GainAdjustment.cpp GainAdjustment.h
	g++ -c GainAdjustment.cpp
LowPassFilter.o: LowPassFilter.cpp LowPassFilter.h
	g++ LowPassFilter.cpp
LowPassFilter.o: AudioModule.cpp AudioModule.h
	g++ AudioModule.cpp
clean: 
	del *.o *.exe *exe.core