#!/bin/bash

#default parameters
NAME="easypaint"
SRC_DIR="../.."
TYPE='-b'
SIGN='-uc -us'
VER=""

function help
{
    cat  << EOF
Usage: make_deb.sh [options] <path-to-source>

Options:
    -h|--help			display help message
    -o|--outdir=DIR		write result to DIR
    -v|--version=VERSION	easypaint version

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
	    shift 
	;;
	-v|--version)
            VER=$2
	    shift
	;;
	*)
	    break;
	;;
    esac
done

#Check, if there is correct source directory
if [ ! -f ${SRC_DIR}/CMakeLists.txt ]; then
    echo "There is no CMakeLists.txt in \"${SRC_DIR}\""
    exit 2
fi

#Set version
if [ -z "$VER" ]; then
    VER=`awk -F'[)( ]' '/set\s*\(EASYPAINT_VERSION / {print($3)}' ${SRC_DIR}/CMakeLists.txt`
fi

OUT_DIR="${HOME}/${NAME}_${VER}_deb"

# TODO: write some messages.

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
cd ${DIR} && dpkg-buildpackage ${TYPE}
