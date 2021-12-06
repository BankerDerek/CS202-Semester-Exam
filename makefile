main: main.cpp WavFileIO.o AudioProcessor.o LowPassFilter.o GainAdjustment.o Normalization.o Compression.o Echo.o 
	g++ -o AudioProcessor.exe main.cpp WavFileIO.o AudioProcessor.o LowPassFilter.o GainAdjustment.o Normalization.o Compression.o Echo.o   
WavFileIO.o: WavFileIO.cpp WavFileIO.h
	g++ -c WavFileIO.cpp
AudioProcessor.o: AudioProcessor.cpp AudioProcessor.h
	g++ -c AudioProcessor.cpp
LowPassFilter.o: LowPassFilter.cpp LowPassFilter.h
	g++ -c LowPassFilter.cpp
GainAdjustment.o: GainAdjustment.cpp GainAdjustment.h
	g++ -c GainAdjustment.cpp
Normalization.o: Normalization.cpp Normalization.h
	g++ -c Normalization.cpp
Compression.o: Compression.cpp Compression.h
	g++ -c Compression.cpp
Echo.o: Echo.cpp Echo.h
	g++ -c Echo.cpp
clean: 
	del *.o *.exe *exe.core
	
	