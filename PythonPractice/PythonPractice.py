import requests
from bs4 import BeautifulSoup

link = "https://coinmarketcap.com/"
responce = requests.get(link).text
soup = BeautifulSoup(responce, 'lxml')
count = 1
result_name = list()
result_symbol = list()
result_price = list()
result_marketCap = list()
while(count < 10):
    block = soup.find('div' , {'class': 'sc-14cb040a-2 hptPYH'})
    block_tr = block.find_all('tr')
    block_td = block_tr[count].find_all('td')
    
    result_name.append(block_td[2].find_all('p')[0].text)
    result_symbol.append(block_td[2].find_all('div')[4].text)
    result_price.append(block_td[3].find('span').text)
    result_marketCap.append(block_td[7].find_all('span')[1].text)
    
    print("name ", result_name[count - 1])
    print("symbol", result_symbol[count - 1])
    print("price", result_price[count - 1])
    print("market Cap", result_marketCap[count - 1])
    print()
    count += 1




