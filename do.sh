#!/bin/sh

./bin/test e1.assembly ${1}
julia datacreate.jl example/e1.assembly.out
./copy.sh
