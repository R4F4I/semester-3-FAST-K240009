# Use an official Python runtime as a parent image
FROM python:3.9-bullseye

# Set the working directory in the container
WORKDIR /app

# Copy the requirements file into the container
COPY requirements.txt .

# Install the required Python packages
RUN pip install --no-cache-dir -r requirements.txt

# Copy the rest of the project files into the container
COPY . .

# Set a non-root user for security (optional but recommended)
RUN useradd -m jupyteruser
USER jupyteruser