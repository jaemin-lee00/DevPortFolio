import urllib.parse
from bs4 import BeautifulSoup
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from import_and_setup.import_and_setup import BUFF_SCORE, BUFF_SCORE_BB, driver

def get_data_from_webpage(search_term):
    search_term_encoded = urllib.parse.quote(search_term)
    url = f'https://dundam.xyz/search?server=adven&name={search_term_encoded}'

    driver.get(url)

    try:
        WebDriverWait(driver, 20).until(
            EC.presence_of_element_located((By.CLASS_NAME, "scon"))
        )
    except:
        print(f"Error loading {url}")

    page_source = driver.page_source
    soup = BeautifulSoup(page_source, 'html.parser')

    data = {
        'name': [],
        'level': [],
        'rank': [],
        'rank25': [],
        'rank40': [],
        'class_pos': []
    }

    scon_divs = soup.find_all('div', {'class': 'scon'})
    if scon_divs:
        for scon_div in scon_divs:
            seh_name_div = scon_div.find('div', {'class': 'seh_name'}, recursive=True)
            name_div = seh_name_div.find('span', {'class': 'name'}, recursive=True)
            
            if name_div:
                name = name_div.contents[0].strip()
                data['name'].append(name)
            else:
                data['name'].append('')

            level_div = seh_name_div.find('div', {'class': 'level'}, recursive=True)
            if level_div:
                level = level_div.get_text().strip()
                data['level'].append(level)
            else:
                data['level'].append('')

            seh_stat_div = scon_div.find('div', {'class': 'seh_stat'}, recursive=True)
            deal_div = seh_stat_div.find('ul', {'class': 'stat_a'}, recursive=True)
            buff_div = seh_stat_div.find('ul', {'class': 'stat_b'}, recursive=True)

            statc_data = {}
            if buff_div:
                statc_spans = buff_div.find_all('span')
                data['class_pos'].append('buff')

                if statc_spans:
                    for i in range(BUFF_SCORE_BB):
                        key = statc_spans[2*i+0].get_text()
                        value = statc_spans[2*i+1].get_text()
                        statc_data[key] = value

            if deal_div:
                tl_fourt_span_flag = deal_div.find('span', {'class': 'tl tfive'}, recursive=True)
                val_span = tl_fourt_span_flag.find_next_sibling('span', {'class': 'val'})

                data['class_pos'].append('deal')

                if val_span:
                    val_text = val_span.get_text().strip()
                    data['rank'].append(val_text)
                else:
                    data['rank'].append('')

            if buff_div:
                if "버프점수" in statc_data:
                    val_span = statc_data['버프점수']
                elif '4인' in statc_data:
                    val_span = statc_data['4인']

                if val_span:
                    data['rank'].append(val_span)
                else:
                    data['rank'].append('')

            if deal_div:
                tl_fourt_span_flag = deal_div.find('span', {'class': 'tl fourt'}, recursive=True)
                val_span = tl_fourt_span_flag.find_next_sibling('span', {'class': 'val'})
                if val_span:
                    val_text = val_span.get_text().strip()
                    data['rank25'].append(val_text)
                else:
                    data['rank25'].append('')

            if buff_div:
                if '2인' in statc_data:
                    val_span = statc_data['2인']
                else:
                    val_span = ''

                if val_span:
                    data['rank25'].append(val_span)
                else:
                    data['rank25'].append('')

            if deal_div:
                tl_ozma_span_flag = deal_div.find('span', {'class': 'tl ozma'}, recursive=True)
                val_span = tl_ozma_span_flag.find_next_sibling('span', {'class': 'val'})
                if val_span:
                    val_text = val_span.get_text().strip()
                    data['rank40'].append(val_text)
                else:
                    data['rank40'].append('')

            if buff_div:
                if '3인' in statc_data:
                    val_span = statc_data['3인']
                else:
                    val_span = ''

                if val_span:
                    data['rank40'].append(val_span)
                else:
                    data['rank40'].append('')
    return data
