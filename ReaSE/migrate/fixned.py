#!/usr/bin/python
# encoding: iso-8859-1

import sys
import re
import os

nedfilename = sys.argv[1]
outfilename = nedfilename + ".fixed"
prepretty = "nedtool -P " + nedfilename
postpretty = "nedtool -P " + outfilename
print "prettyfying input file"
os.system(prepretty)
nedfile = open(nedfilename, "r")
outfile = open(outfilename, "w")
inas = 0
incore = 0
inmod = 0
ininet = 0
inasmod = 0
propertydone = 0
print "fixing properties and gates"
for line in nedfile:
	chanline = re.search('.*?datarate = (.*?)\*.+', line, re.DOTALL)
	if chanline:
		newline = "datarate = " + chanline.group(1) + "Mbps;\n"
		outfile.write(newline)
		continue
	
	if line.find("module Internet") >= 0:
		ininet = 1
	if line == "{\n" and ininet and not propertydone:
		outfile.write(line)
		outfile.write("parameters:\n")
		outfile.write("@Internet();\n")
		propertydone = 1
		continue
	
	asline = re.search('.*?as\d+:.+?AS\d+.+?{.+', line, re.DOTALL)
	if asline and ininet:
		inasmod = 1
	if line.find("parameters:") >= 0 and inasmod:
		outfile.write(line)
		outfile.write("@AS();\n")
		inasmod = 0
		continue
	
	if line.find("module TAS") >= 0 or line.find("module SAS") >= 0:
		inas = 1
		ininet = 0
	
	coregatelinein = re.search('(.+?)\.in\+\+(.+)', line, re.DOTALL)
	coregatelineout = re.search('(.+?)\.out\+\+(.+)', line, re.DOTALL)
	gateline = re.search('(.+?)\.out\+\+(.+?)\.in\+\+(.+)', line, re.DOTALL)
	if gateline and inas:
		newline = gateline.group(1) + ".pppg$o++" + gateline.group(2) + ".pppg$i++" + gateline.group(3)
		outfile.write(newline)
		continue
	if coregatelinein and inas:
		newline = coregatelinein.group(1) + ".pppg$i++" + coregatelinein.group(2)
		outfile.write(newline)
		continue
	if coregatelineout and inas:
		newline = coregatelineout.group(1) + ".pppg$o++" + coregatelineout.group(2)
		outfile.write(newline)
		continue
	
	coreline = re.search('.*?core\d+:.+?{.+', line, re.DOTALL)
	if coreline and inas:
		incore = 1
	if line.find("parameters:") >= 0 and incore:
		outfile.write(line)
		outfile.write("@CoreRouter();\n")
		outfile.write("@RL();\n")
		incore = 0
		continue
	
	moduleline = re.search('.*?\d+:.+?{.+', line, re.DOTALL)
	if moduleline and inas:
		inmod = 1
	if line.find("parameters:") >= 0 and inmod:
		outfile.write(line)
		outfile.write("@RL();\n")
		inmod = 0
		continue
	
	outfile.write(line)

outfile.close()
print "prettyfying output file"
os.system(postpretty)