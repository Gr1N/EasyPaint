#!/bin/bash

#default parameters
NAME="easypaint"
SRC_DIR="../.."
TYPE='-b'
SIGN='-uc -us'
VER=""
OUT_DIR=""

function help
{
    cat  << EOF
Usage: make_deb.sh [options] <path-to-sources>
By default path-to-sources is ${SRC_DIR}

Options:
    -h|--help			display help message
    -o|--outdir=DIR		write result to DIR, by default it's home dir
    -v|--version=VERSION	easypaint version
    -s				make source package, if ommited make binary package
    -S|--sign			sign package

EOF
}

while [ ! -z "$1" ]; do
    case $1 in
        -h|--help)
            help
	    exit
	;;
	-o|--outdir)
            OUT_DIR=$2
	    shift 2
	;;
	-v|--version)
            VER=$2
	    shift 2
	;;
	-s)
	    TYPE='-S'
	    shift
	;;
	-S|--sign)
            SIGN=''
	    shift
	;;
	*)
	    SRC_DIR=$1
	    break
	;;
    esac
done

if [ -z "$OUT_DIR" ]; then
    OUT_DIR="${HOME}/${NAME}_${VER}_deb"
fi

#Check, if there is correct source directory
if [ ! -f ${SRC_DIR}/CMakeLists.txt ]; then
    echo "There is no CMakeLists.txt in \"${SRC_DIR}\""
    exit 2
fi

#Set version
if [ -z "$VER" ]; then
    VER=`awk -F'[)( ]' '/set\s*\(EASYPAINT_VERSION / {print($3)}' ${SRC_DIR}/CMakeLists.txt`
fi

# TODO: write some messages.
echo Build ${NAME} package...
echo Src dir: ${SRC_DIR}
echo Out dir: ${OUT_DIR}
echo ........................

OUT_DIR=`readlink -m ${OUT_DIR}`
mkdir -p ${OUT_DIR} || exit 2
DIR=${OUT_DIR}/${NAME}-${VER}
rm -rf ${DIR}

#copying sources to the destination dir
cp -r ${SRC_DIR} ${DIR}
rm -rf ${DIR}/.git ${DIR}/build ${DIR}/distr

mkdir ${DIR}/debian
cp -r ${SRC_DIR}/distr/deb/debian ${DIR}

#Build package
cd ${DIR}/.. && tar cjf ${NAME}_${VER}.orig.tar.bz2 ${NAME}-${VER}
cd ${DIR} && dpkg-buildpackage ${TYPE} ${SIGN}

#clean OUT_DIR
rm -rf ${DIR}
rm ../${NAME}_${VER}.orig.tar.bz2

echo Now you can find deb package at ${OUT_DIR}
