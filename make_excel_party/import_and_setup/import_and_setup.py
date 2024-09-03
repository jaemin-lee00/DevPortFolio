import requests
from bs4 import BeautifulSoup
import pandas as pd
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import os
import json


# Selenium 설정
chrome_options = Options()
chrome_options.add_argument("--headless")
chrome_options.add_argument("--no-sandbox")
chrome_options.add_argument("--disable-dev-shm-usage")

chrome_driver_path = ChromeDriverManager().install()
print(f"ChromeDriver installed at: {chrome_driver_path}")



try:
    # ChromeDriver 설치 경로 확인
    chrome_driver_path = ChromeDriverManager().install()
    print(f"ChromeDriver installed at: {chrome_driver_path}")

    # 경로가 THIRD_PARTY_NOTICES.chromedriver로 끝나는 경우 수정
    if not chrome_driver_path.endswith("chromedriver.exe"):
        chrome_driver_dir = os.path.dirname(chrome_driver_path)
        chrome_driver_path = os.path.join(chrome_driver_dir, "chromedriver.exe")

    # ChromeDriver가 존재하는지 확인
    if not os.path.exists(chrome_driver_path):
        raise FileNotFoundError(f"ChromeDriver not found at path: {chrome_driver_path}")

    # 서비스 설정 및 WebDriver 시작
    service = Service(chrome_driver_path)
    driver = webdriver.Chrome(service=service, options=chrome_options)
    print("ChromeDriver started successfully")

except Exception as e:
    print(f"Error occurred: {e}")

def read_json_file(file_path):
    # JSON 파일을 열고 데이터 읽기
    with open(file_path, 'r', encoding='utf-8') as file:
        data = json.load(file)
    return data

# 현재 파일의 디렉토리를 기준으로 상위 경로 계산
current_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(current_dir, '..', 'data_input', 'data.json')

# JSON 데이터 읽기
json_data = read_json_file(file_path)

BUFF_SCORE = 1
BUFF_SCORE_BB = 3

# 드라이버 종료 함수
def close_driver():
    driver.quit()
    print("ChromeDriver quit successfully")
