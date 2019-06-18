# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g -Werror -std=c++11

# ****************************************************
# Targets needed to bring the executable up to date

main: p4.o pwdCheck.o excessC.o compundC.o Flip.o FlipPwdCheck.o FlipExcessC.o FlipCompundC.o
	$(CXX) $(CXXFLAGS) -o main p4.o pwdCheck.o excessC.o compundC.o Flip.o FlipPwdCheck.o FlipExcessC.o FlipCompundC.o

# The main.o target can be written more simply

main.o: p4.cpp pwdCheck.h excessC.h compundC.h Flip.h FlipPwdCheck.h FlipExcessC.h FlipCompundC.h
	$(CXX) $(CXXFLAGS) -c p4.cpp

Parents.o: pwdCheck.h Flip.h

Children.o:  compundC.h excessC.h pwdCheck.h Flip.h FlipPwdCheck.h FlipExcessC.h FlipCompundC.h
