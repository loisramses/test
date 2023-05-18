CC = gcc
MPICC = mpicc 
CFLAGS = -Wall -fopenmp

SEQUENTIAL = dtw_sequencial.c
OMP = dtw_omp.c
MPI = dtw_mpi.c

TEST_FILES0 = RefFrom0to500.txt TestFrom0to500.txt
TEST_FILES1 = RefFrom0to1000.txt TestFrom0to1000.txt
TEST_FILES2 = RefFrom0to2000.txt TestFrom0to2000.txt
TEST_FILES3 = RefFrom0to3000.txt TestFrom0to3000.txt
TEST_FILES4 = RefFrom0to4000.txt TestFrom0to4000.txt
TEST_FILES5 = RefFrom0to5000.txt TestFrom0to5000.txt
TEST_FILES6 = RefFrom0to6000.txt TestFrom0to6000.txt
TEST_FILES7 = RefFrom0to7000.txt TestFrom0to7000.txt
TEST_FILES8 = RefFrom0to8000.txt TestFrom0to8000.txt
TEST_FILES9 = RefFrom0to9000.txt TestFrom0to9000.txt
TEST_FILES10 = RefFrom0to10000.txt TestFrom0to10000.txt
TEST_FILES11 = RefFrom0to11000.txt TestFrom0to11000.txt
TEST_FILES12 = RefFrom0to12000.txt TestFrom0to12000.txt
TEST_FILES13 = RefFrom0to13000.txt TestFrom0to13000.txt
TEST_FILES14 = RefFrom0to14000.txt TestFrom0to14000.txt
TEST_FILES15 = RefFrom0to15000.txt TestFrom0to15000.txt
TEST_FILES16 = RefFrom0to16000.txt TestFrom0to16000.txt
TEST_FILES17 = RefFrom0to17000.txt TestFrom0to17000.txt
TEST_FILES18 = RefFrom0to18000.txt TestFrom0to18000.txt
TEST_FILES19 = RefFrom0to19000.txt TestFrom0to19000.txt
TEST_FILES20 = RefFrom0to20000.txt TestFrom0to20000.txt
TEST_FILES21 = RefFrom0to21000.txt TestFrom0to21000.txt
TEST_FILES22 = RefFrom0to22000.txt TestFrom0to22000.txt
TEST_FILES24 = RefFrom0to24000.txt TestFrom0to24000.txt
TEST_FILES26 = RefFrom0to26000.txt TestFrom0to26000.txt
TEST_FILES28 = RefFrom0to28000.txt TestFrom0to28000.txt
TEST_FILES30 = RefFrom0to30000.txt TestFrom0to30000.txt

.PHONY: all run

all: dtw_sequencial dtw_omp dtw_mpi teste_sequencial teste_omp teste_mpi

run: teste_sequencial teste_omp teste_mpi

teste_sequencial: dtw_sequencial
	./dtw_sequencial $(TEST_FILES0)
	./dtw_sequencial $(TEST_FILES1)
	./dtw_sequencial $(TEST_FILES2)
	./dtw_sequencial $(TEST_FILES3)
	./dtw_sequencial $(TEST_FILES4)
	./dtw_sequencial $(TEST_FILES5)
	./dtw_sequencial $(TEST_FILES6)
	./dtw_sequencial $(TEST_FILES7)
	./dtw_sequencial $(TEST_FILES8)
	./dtw_sequencial $(TEST_FILES9)
	./dtw_sequencial $(TEST_FILES10)
	./dtw_sequencial $(TEST_FILES11)
	./dtw_sequencial $(TEST_FILES12)
	./dtw_sequencial $(TEST_FILES13)
	./dtw_sequencial $(TEST_FILES14)
	./dtw_sequencial $(TEST_FILES15)
	./dtw_sequencial $(TEST_FILES16)
	./dtw_sequencial $(TEST_FILES17)
	./dtw_sequencial $(TEST_FILES18)
	./dtw_sequencial $(TEST_FILES19)
	./dtw_sequencial $(TEST_FILES20)
	./dtw_sequencial $(TEST_FILES21)
	./dtw_sequencial $(TEST_FILES22)
	./dtw_sequencial $(TEST_FILES24)
	./dtw_sequencial $(TEST_FILES26)
	./dtw_sequencial $(TEST_FILES28)
	./dtw_sequencial $(TEST_FILES30)

teste_omp: dtw_omp
	./dtw_omp $(TEST_FILES0)
	./dtw_omp $(TEST_FILES1)
	./dtw_omp $(TEST_FILES2)
	./dtw_omp $(TEST_FILES3)
	./dtw_omp $(TEST_FILES4)
	./dtw_omp $(TEST_FILES5)
	./dtw_omp $(TEST_FILES6)
	./dtw_omp $(TEST_FILES7)
	./dtw_omp $(TEST_FILES8)
	./dtw_omp $(TEST_FILES9)
	./dtw_omp $(TEST_FILES10)
	./dtw_omp $(TEST_FILES11)
	./dtw_omp $(TEST_FILES12)
	./dtw_omp $(TEST_FILES13)
	./dtw_omp $(TEST_FILES14)
	./dtw_omp $(TEST_FILES15)
	./dtw_omp $(TEST_FILES16)
	./dtw_omp $(TEST_FILES17)
	./dtw_omp $(TEST_FILES18)
	./dtw_omp $(TEST_FILES19)
	./dtw_omp $(TEST_FILES20)
	./dtw_omp $(TEST_FILES21)
	./dtw_omp $(TEST_FILES22)
	./dtw_omp $(TEST_FILES24)
	./dtw_omp $(TEST_FILES26)
	./dtw_omp $(TEST_FILES28)
	./dtw_omp $(TEST_FILES30)

teste_mpi: dtw_mpi
	mpiexec -np 1 ./dtw_mpi $(TEST_FILES10)
	mpiexec -np 2 ./dtw_mpi $(TEST_FILES10)
	mpiexec -np 3 ./dtw_mpi $(TEST_FILES10)
	mpiexec -np 4 ./dtw_mpi $(TEST_FILES10)

dtw_sequencial:
	@echo "compiling dtw_sequencial"
	@$(CC) $(CFLAGS) $(SEQUENTIAL) -o $@

dtw_omp:
	@echo "compiling dtw_omp"
	@$(CC) $(CFLAGS) $(OMP) -o $@

dtw_mpi:
	@echo "compiling dtw_mpi"
	@$(MPICC) $(MPI) $(CFLAGS) -o $@

cleanup:
	@rm *.out

