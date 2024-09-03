import pandas as pd
import numpy as np
from data_manage.data_scraping import get_data_from_webpage
from import_and_setup.import_and_setup import json_data
import re

WEIGHT_FOR_DEAL_UNIT = 100

def check_std(target_means) :
    # means 리스트를 numpy 배열로 변환
    means_array = np.array(target_means)
    # numpy 배열의 표준 편차를 계산 (모집단 표준 편차)
    print(means_array.std(ddof=0))

def clean_value(value):
    # 콤마 제거, 단위 표시 제거 (예: '원')
    clean_val = re.sub(r'[^\d]', '', value)
    return int(clean_val) if clean_val else None

def make_list_mean(get_means) :
    return get_means.apply(clean_value).mean()

def round_to_buff_unit(number) : 
    return round(number / 10000) 

def buff_to_deal(get_buff) :
    standard_deal = 5000
    standard_buff = 180
    return (get_buff - standard_buff) * WEIGHT_FOR_DEAL_UNIT + standard_deal

def get_party_mean(get_party_buff, get_party_deal) :

    buff_to_unit = round_to_buff_unit(clean_value(get_party_buff))    
    mean_of_deal = make_list_mean(get_party_deal)

    weight_for_deal = buff_to_deal(buff_to_unit)
    mean_of_party = round((mean_of_deal + weight_for_deal)/2)

    return mean_of_party

def process_data(adven_names):
    all_data = []

    for adven_name in adven_names:
        data = get_data_from_webpage(adven_name)
        df = pd.DataFrame(data)
        df.insert(0, 'search_term', '')
        if not df.empty:
            df.at[0, 'search_term'] = adven_name
        all_data.append(df)

        empty_row = pd.DataFrame([[''] * len(df.columns)], columns=df.columns)
        all_data.append(empty_row)

    combined_df = pd.concat(all_data, ignore_index=True)

    deal_rows = combined_df[combined_df['class_pos'] == 'deal']
    buff_rows = combined_df[combined_df['class_pos'] == 'buff']

    party_data = get_party_data(deal_rows, buff_rows)

    return combined_df, party_data

BUFF_UNIT = 10000

def get_party_high_dungeon(get_deal_data, get_buff_data) :

    high_dungeon_data = json_data['dungeon'].get('high-dungeon', {})
    deal_cut = high_dungeon_data.get('deal_cut')
    buff_cut = high_dungeon_data.get('buff_cut')

    high_dungeon_buffs = get_buff_data[get_buff_data['rank'].apply(clean_value) >= buff_cut*BUFF_UNIT]
    high_dungeon_deals = get_deal_data[get_deal_data['rank'].apply(clean_value) >= deal_cut]

    # Buff 데이터 정렬
    sorted_high_dungeon_buffs = high_dungeon_buffs.sort_values(by='rank', ascending=True)

    # Deal 데이터 정렬
    sorted_high_dungeon_deals = high_dungeon_deals.sort_values(by='rank', ascending=True)

    # 파티 리스트 초기화
    partys_high_dungeon = []

    for i in range(min(len(sorted_high_dungeon_buffs), len(sorted_high_dungeon_deals) // 3)):
        # Buff에서 1개의 개체 선택0

        buff = sorted_high_dungeon_buffs.iloc[i]
        cleaned_buff = sorted_high_dungeon_buffs.iloc[i]
        cleaned_buff['rank'] = clean_value(cleaned_buff['rank'])

        len_of_party = min(len(sorted_high_dungeon_buffs), len(sorted_high_dungeon_deals) // 3)
        # Deals에서 3개의 개체 선택
        
        deals = sorted_high_dungeon_deals.iloc[i:i + len_of_party*2 + 1: len_of_party]
        cleaned_deals = sorted_high_dungeon_deals.iloc[i:i + len_of_party*2 + 1: len_of_party]
        cleaned_deals['rank'] = cleaned_deals['rank'].apply(clean_value)

        # 하나의 파티 구성 (예시로 rank와 다른 컬럼을 사용)
        party = {
            'buff': (cleaned_buff['name'], cleaned_buff['rank']),
            'deals': [(deal['name'], deal['rank']) for index, deal in cleaned_deals.iterrows()],
            'means' : get_party_mean(buff['rank'],deals['rank'])
        }
        
        # 파티 리스트에 추가
        partys_high_dungeon.append(party)

    clean_of_deals = high_dungeon_deals['rank'].apply(clean_value)

    buff_to_clean_unit = high_dungeon_buffs['rank'].apply(clean_value).apply(round_to_buff_unit)
    clean_of_buffs_to_deal = buff_to_clean_unit.apply(buff_to_deal)

    std_of_party_S = pd.concat([clean_of_deals, clean_of_buffs_to_deal], ignore_index=True)

    # means = partys_high_dungeon  # means는 partys_high_dungeon을 참조
    # for dungeon in means:
    #     dungeon['means'] = sorted(dungeon['means'])

    # check_std(means)





    return 0
       
def get_party_data(deal_data_rows, buff_data_rows):

    buff_num = len(buff_data_rows)
    deal_num = len(deal_data_rows)

    get_party_high_dungeon(deal_data_rows,buff_data_rows)

    party_data = {}

    # 원하는 데이터 처리 로직을 여기에 작성하세요.
    return party_data
