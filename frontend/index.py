import streamlit as st
import pandas as pd
import time
import requests

# Initialize session state if not exists
if 'sensor_data' not in st.session_state:
    st.session_state.sensor_data = []

st.title("Real-time Sensor Data")

# Create a placeholder for the data
chart_placeholder = st.empty()
data_placeholder = st.empty()

# Update function
def update_data():
    try:
        response = requests.get('http://localhost:3000')
        if response.status_code == 200:
            st.session_state.sensor_data = response.json()
            
            # Convert to DataFrame for better visualization
            df = pd.DataFrame(st.session_state.sensor_data)
            
            # Update visualizations
            with chart_placeholder:
                st.line_chart(df.set_index('timestamp')['value'])
    except Exception as e:
        st.error(f"Error fetching data: {e}")

# Create auto-refresh
if st.button('Start Auto-refresh'):
    while True:
        update_data()
        time.sleep(1)  # Refresh every second
