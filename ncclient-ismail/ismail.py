import traceback
import xml.dom.minidom
from ncclient import manager
from ncclient.xml_ import to_ele

# NETCONF Sunucu Bilgileri
host = "localhost"
port = 830
user = "root"
password = "1"

# XML Formatlama Fonksiyonu
def print_formatted(xml_string):
    try:
        print(xml.dom.minidom.parseString(xml_string).toprettyxml())
    except Exception as e:
        print("Hata: XML formatlanamadı.")
        print(traceback.format_exc())

try:
    # NETCONF Bağlantısını Başlat
    with manager.connect(
        host=host,
        port=port,
        username=user,
        password=password,
        hostkey_verify=False
    ) as m:
        print("✅ NETCONF sunucusuna başarıyla bağlanıldı!")

        # Belirli Alanları Çekmek İçin GET Sorgusu
        get_message = '''<nc:get xmlns:nc="urn:ietf:params:xml:ns:netconf:base:1.0">
          <nc:filter type="subtree">
            <netconf-state xmlns="urn:ietf:params:xml:ns:yang:ietf-netconf-monitoring">
              <capabilities/>
              <sessions/>
            </netconf-state>
          </nc:filter>
        </nc:get>'''

        # Sorguyu Gönder ve Yanıtı Al
        get_response = m.dispatch(to_ele(get_message))
        print("Get Yanıtı:")
        print_formatted(get_response.xml)

except Exception as e:
    print(f" Hata: {e}")
    traceback.print_exc()
