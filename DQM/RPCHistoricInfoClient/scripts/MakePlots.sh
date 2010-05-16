#!/bin/sh

Database=$1
TagName=$2
Password=$3
RunStart=$4
RunEnd=$5

PlotDir="CurrentPlots"

rm -rf $PlotDir

if [ $5 ]; then
RPCHDQMInspector $Database $TagName $Password $RunStart $RunEnd
else
RPCHDQMInspector $Database $TagName $Password $RunStart
fi
mkdir -pv $PlotDir
mv *.gif $PlotDir
mv *.eps $PlotDir
cp diow.pl $PlotDir
cd $PlotDir
./diow.pl
cd ..

