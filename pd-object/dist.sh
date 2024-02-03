DIR="/Applications/Pd-0.53-2.app/Contents/Resources/extra/intraconnection_adc/"

if [[ ! -d ${DIR} ]]; then
    mkdir ${DIR}
fi

cp intraconnection_adc.pd_darwin libintraconnection_adc.pd_darwin.dylib ${DIR}
echo "Files copied: \n"`printf '%s \\\n' ${DIR}*.*`
