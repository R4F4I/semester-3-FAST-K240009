import pywhatkit
import datetime
import time

# --- Configuration ---
# 1. Replace with the recipient's phone number, including the country code (e.g., +11234567890)
recipient_phone = "+923362156875" 
message_text = "This message was sent instantly using Python!"

# 2. Calculate a time 2 minutes into the future
now = datetime.datetime.now()
# Add 2 minutes to the current time to meet the library's minimum time requirement
send_time = now + datetime.timedelta(minutes=2) 

send_hour = send_time.hour
send_minute = send_time.minute

# --- Execution ---
print(f"Current time: {now.strftime('%H:%M:%S')}")
print(f"Scheduling message to {recipient_phone} at {send_hour}:{send_minute:02d}...")

try:
    # Arguments: phone_number, message, hour, minute, wait_time_seconds, close_tab
    # 15: wait time in seconds before sending message after browser opens
    # True: close the tab after sending
    # 3: seconds before closing tab
    pywhatkit.sendwhatmsg(
        recipient_phone,
        message_text,
        send_hour,
        send_minute,
        15,
        True,
        3
    )

    print("\n✅ Script executed. Wait for the scheduled time.")
    print("Your browser will open and send the message automatically.")
    
except Exception as e:
    print(f"\n❌ An error occurred: {e}")
    print("Ensure your phone number is correct and you are logged into WhatsApp Web.")