main: main.cpp GainAdjustment.o GainAdjustment.h LowPassFilter.o LowPassFilter.h
	g++ -o AudioProcessor.exe main.cpp GainAdjustment.o
GainAdjustment.o: GainAdjustment.cpp GainAdjustment.h
	g++ -c GainAdjustment.cpp
LowPassFilter.o: LowPassFilter.cpp LowPassFilter.h
	g++ -c LowPassFilter.cpp
clean: 
	del *.o *.exe *exe.core