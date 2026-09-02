from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.keys import Keys
from webdriver_manager.chrome import ChromeDriverManager
import time
import csv

# Setup driver
driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()))

url = "https://dau-main-exams.hf.space/view_schedule/"
driver.get(url)
time.sleep(2)  # wait for page to load

# Prepare IDs and data container
student_ids = [f"202412{str(i).zfill(3)}" for i in range(125)]
date = "25-12-2025"
all_data = []

for sid in student_ids:
    try:
        # Clear and fill inputs
        input_id = driver.find_element(By.XPATH, '//input[@placeholder="Enter your student ID"]')
        input_date = driver.find_element(By.XPATH, '//input[@placeholder="dd-mm-yyyy"]')

        input_id.clear()
        input_date.clear()

        input_id.send_keys(sid)
        input_date.send_keys(date)

        # Click submit button
        driver.find_element(By.XPATH, '//button[text()="Search Schedule"]').click()
        time.sleep(1.5)  # wait for results

        # Find result table rows
        rows = driver.find_elements(By.XPATH, '//table//tr')[1:]  # skip header

        for row in rows:
            cols = [col.text for col in row.find_elements(By.TAG_NAME, "td")]
            if cols:
                all_data.append(cols)
                print(f"{sid}: {cols}")

    except Exception as e:
        print(f"Error for {sid}: {e}")
    time.sleep(0.5)

# Save to CSV
with open("exam_schedule.csv", "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["Student Name", "Student ID", "Exam Date", "Room Number", "Subject Name", "Subject Code", "Seat Number"])
    writer.writerows(all_data)

driver.quit()
print("✅ All done!")
