import requests
import sys
import os
import time
from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.chrome.options import Options

cert_file_path = "cert.pem"
key_file_path = "key2.pem"

output_file = open('runfilestemp.txt','w')
output_file2 = open('runfiles.txt','w')

def getFiles(run):

    if run<319337:
        ULversion = "-v2"
    else:
        ULversion = "_rsb-v1"
    url = "https://cmsweb.cern.ch/das/request?input=file%2Cdataset%3D%2FZeroBias%2FRun2018A-12Nov2019_UL2018"+ULversion+"%2FAOD+run%3D"+run+"&instance=prod/global&idx=0&limit=500"
    #url = "https://cmsweb.cern.ch/das/request?view=plain&instance=prod%2Fglobal&input=file%2Cdataset%3D%2FZeroBias%2FRun2018A-12Nov2019_UL2018"+ULversion+"%2FAOD+run%3D"+run
    #params = {"param_1": "value_1", "param_2": "value_2"}
    #cert = (cert_file_path, key_file_path)
    #r = requests.get(url, params=params, cert=cert)
    #time.sleep(60)
    #soup = BeautifulSoup(r.content, 'html.parser')
    #linenum=0
    #lines = soup.find_all(text=lambda text: text.startswith('/store'))
    #for line in lines:
    #    print(line)
    #print(soup)
    #print(r.content)
    #output_file.write(r.text)

    options = Options()
    options.add_argument('--headless')  # Run the browser in headless mode (without GUI)
    options.add_argument('--ignore-certificate-errors')  # Ignore certificate errors
    options.add_argument('--user-data-dir=/path/to/user/data')  # Specify the user data directory (optional)
    options.add_argument('--disable-web-security')  # Disable web security to allow insecure certificate

    driver = webdriver.Chrome(options=options)

    # Set the path to your certificate file
    certificate_file = 'cert.pem'

    # Set the path to your key file
    key_file = 'key2.pem'

    # Load the certificate and key
    driver.get('chrome://settings/certificates')
    time.sleep(2)

    driver.find_element_by_id('Import').click()
    time.sleep(1)

    driver.find_element_by_id('file-path').send_keys(certificate_file)
    time.sleep(1)

    driver.find_element_by_id('password').send_keys('juveBIG99!')  # Provide the password if required
    time.sleep(1)

    driver.find_element_by_id('Import').click()
    time.sleep(2)

    driver.find_element_by_id('YourCertificates').click()
    time.sleep(1)

    driver.find_element_by_id('Import').click()
    time.sleep(1)

    driver.find_element_by_id('file-path').send_keys(key_file)
    time.sleep(1)

    driver.find_element_by_id('password').send_keys('key_password')  # Provide the password if required
    time.sleep(1)

    driver.find_element_by_id('Import').click()
    time.sleep(2)

    # Navigate to the desired URL
    driver.get(url)
    time.sleep(5)  # Wait for the page to load (adjust as needed)

    # Get the HTML content after JavaScript execution
    html_content = driver.page_source

    # Parse the HTML content using Beautiful Soup
    soup = BeautifulSoup(html_content, 'html.parser')

    # Find all text lines that start with 'name'
    lines = soup.find_all(text=lambda text: text.startswith('name'))

    print(soup)

    driver.quit()
    # ...


run=sys.argv[1]

getFiles(run)

output_file.close()

input_file = open('runfilestemp.txt','r')

for line in input_file:
    if line.startswith("name"):
        filename=line.split('"')[1]
        output_file2.write(' inputFiles_.push_back("root://cms-xrd-global.cern.ch/')
        output_file2.write(filename+'");')
        output_file2.write("\n")

input_file.close()
output_file2.close()
#os.remove("runfilestemp.txt")
