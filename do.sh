#!/bin/sh

./bin/test e1.assembly
julia datacreate.jl example/e1.assembly.out
./copy.sh
