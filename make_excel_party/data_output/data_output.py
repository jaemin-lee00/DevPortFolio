import os
import pandas as pd
import sys

# 상위 디렉토리의 모듈을 임포트하기 위해 경로 추가
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from import_and_setup.import_and_setup import close_driver
from import_and_setup.import_and_setup import json_data

from data_manage.data_processing import process_data

def save_to_excel(combined_df):
    save_path = os.getenv('EXCEL_SAVE_PATH', '.')
    if not os.path.exists(save_path) :
        print(f"Warning: The specified path {save_path} does not exist. Using current directory instead.")
        save_path = '.'

    output_file = os.path.join(save_path, "combined_data.xlsx")

    combined_df.to_excel(output_file, index=False)
    print(f"Data saved to {output_file}")

    close_driver()

# 사용자로부터 검색어 입력받기
adven_names = json_data.get('adven_name', [])
dungeon_names = json_data.get('dungeon',[])


# 데이터 처리 및 저장
# 파티 데이터 시트 2 저장
combined_df, party_data = process_data(adven_names)
save_to_excel(combined_df)
