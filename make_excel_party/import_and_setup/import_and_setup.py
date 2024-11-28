import requests
from bs4 import BeautifulSoup
import pandas as pd
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import os
import json
import time


# Selenium 설정
chrome_options = Options()
chrome_options.add_argument("--headless")
chrome_options.add_argument("--no-sandbox")
chrome_options.add_argument("--disable-dev-shm-usage")

try:
    # ChromeDriver 경로 설정 (직접 다운로드한 경로로 변경)
    chrome_driver_path = "C:/Users/Admin/Documents/GitHub/DevPortFolio/make_excel_party/chromedriver.exe"
    print(f"ChromeDriver path set to: {chrome_driver_path}")

    # ChromeDriver가 존재하는지 확인
    if not os.path.exists(chrome_driver_path):
        raise FileNotFoundError(f"ChromeDriver not found at path: {chrome_driver_path}")

    # 잠시 대기 (Windows Defender 등의 간섭을 피하기 위해)
    time.sleep(5)

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
