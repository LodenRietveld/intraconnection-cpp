DIR="/home/sound/Documents/Pd/externals/intraconnection_adc/"

if [[ ! -d ${DIR} ]]; then
    mkdir ${DIR}
fi

cp intraconnection_adc.pd_linux libintraconnection_adc.pd_linux.so ${DIR}
echo "Files copied: \n"`printf '%s \\\n' ${DIR}*.*`
