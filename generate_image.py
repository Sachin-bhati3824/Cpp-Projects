import asyncio
from playwright.async_api import async_playwright
import time 
import sys 
import os 
import urllib.request
import datetime 
from pathlib import Path

script_dir = Path(__file__).parent.absolute()

# 2. Define the gallery path
gallery_path = script_dir / "output_gallery"

# 3. Create the folder if it doesn't exist
gallery_path.mkdir(parents=True, exist_ok=True)

# 4. Format the time (REMOVED colons for Windows compatibility)
timestamp = datetime.datetime.now().strftime("%Y-%m-%d_%I-%M-%S_%p")

# 5. Define the filenames
latest_file = str(script_dir / "currently_generated.jpg") # For the C++ GUI to find easily
gallery_file = str(gallery_path / f"{timestamp}.jpg")
async def genrate_image(prompt):
    target_prompt = prompt  
    async with async_playwright() as p:
        browser = await p.chromium.launch(headless=True)
        page = await browser.new_page()
        
        await page.goto('https://deepai.org/machine-learning-model/text2img')
        
        # 2. Fill the prompt
        await page.fill('textarea[placeholder="Describe what you\'d like to generate"]',target_prompt)
        
        # 3. Click Generate (DeepAI handles the timing automatically)
        await page.get_by_role("button", name="Generate").click()
        download_button = page.locator('button#download-button[imagewasgenerated="True"]')
        await download_button.wait_for(state="visible")
        image = page.locator("#main-image")
        await image.wait_for(state="visible")
        # 4. Wait for the output image to appear
        # We wait for the image tag with the specific class 'output-img'
        time.sleep(5)
        image = page.locator("#main-image")
        await image.wait_for(state="visible")
        image_url = await image.get_attribute("src")
        urllib.request.urlretrieve(image_url,latest_file)
        urllib.request.urlretrieve(image_url,gallery_file)
        print(f"success")
        await browser.close()


if __name__ == "__main__":
    if(len(sys.argv) > 1):
        user_prompt = " ".join(sys.argv[1:])
        asyncio.run(genrate_image(user_prompt))