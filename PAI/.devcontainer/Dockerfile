# Start from the official Jupyter base notebook image
FROM jupyter/base-notebook:latest

# Switch to the jovyan user to install packages
USER $NB_UID

# Copy requirements from the parent directory and install
COPY ../requirements.txt /tmp/
RUN pip install --no-cache-dir -r /tmp/requirements.txt
