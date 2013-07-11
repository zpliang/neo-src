# purpose: wrapper for CPF2tb.exe.
# 1, Ich will read CPF header and give [MJDbegin].
# 2, Ich will split output and rename with template 'tbmmddhh.xx'

# usage: [==] <CPFfile> <span days>
#

infile=$1
span=$2

if [ -z ${span}]; 
    then span=1; 
fi

# set paths
fullname=`readlink -f $0`
mypath=${fullname%/*}

fnameext=${0##*/}
thisname=${fnameext%%.*}
sfx=${thisname}.tmp

trunk=_CPF_10trunk_$sfx
outfile=_output_all__$sfx


# get trunk
cat ${infile} | grep '^10' > ${trunk}

# get satname
satname=`head ${infile} | awk '/^H1/{print substr($10,0,2)}'`

# tb header line 1
line1="#2013/00/00          TB USED:    0"
# tb header line 2
line2="#SATELLITE  ${satname}    760.0   20.0   80.0"
# 1. find MJDbegin.
MJDbegin=`head -n20  ${trunk} | tail -n1 | awk '{print $3}'`

# call exe.
${mypath}/CPF2tb.exe ${trunk} chan7237dat.txt ${MJDbegin} ${span} > ${outfile}

# 2, split.
csplit ${outfile} -z -b '%02d.tmp' /^\#T/ {*}
for f in `ls xx*.tmp` 
do
    fn=`head ${f} | awk '/^##/{print $2}'`".${satname}"
    echo "${line1}" >  ${fn}
    echo "${line2}" >> ${fn}
    cat ${f} | grep -v '^##' >> ${fn}
done

