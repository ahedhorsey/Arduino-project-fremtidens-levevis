// Fetch and display the schedule table
function fetchSchedule() {
    fetch("/api/schedule")
        .then(response => response.json())
        .then(data => {
            const tableBody = document.querySelector("#scheduleTable tbody");
            tableBody.innerHTML = ""; // Clear existing table rows

            let maxValuesPerDay = new Array(7).fill(0); // Track max value for each day

            // First pass: Find the highest activation value per day
            for (let day = 0; day < 7; day++) {
                for (let hour = 0; hour < 24; hour++) {
                    let value = data.schedule[day][hour] || 0;
                    if (value > maxValuesPerDay[day]) {
                        maxValuesPerDay[day] = value;
                    }
                }
            }

            // Second pass: Build the table and apply highlighting
            for (let hour = 0; hour < 24; hour++) {
                let row = document.createElement("tr");

                // Hour label
                let hourCell = document.createElement("td");
                hourCell.innerText = hour + ":00";
                row.appendChild(hourCell);

                // Loop through days (Monday to Sunday)
                for (let day = 0; day < 7; day++) {
                    let cell = document.createElement("td");
                    let value = data.schedule[day][hour] || 0;
                    cell.innerText = value.toFixed(1);

                    // Highlight only if it matches the max value found in the first pass
                    if (value === maxValuesPerDay[day] && value > 0) {
                        cell.classList.add("highlight");
                    }

                    row.appendChild(cell);
                }

                tableBody.appendChild(row);
            }
        })
        .catch(error => console.log("Error fetching API data:", error));
}


// Handle the datetime picker and send the selected time to the server
document.getElementById("setTimeButton").addEventListener("click", () => {
    const datetimeInput = document.getElementById("datetimePicker").value;

    if (datetimeInput) {
        const selectedDate = new Date(datetimeInput);
        const unixTimestamp = Math.floor(selectedDate.getTime() / 1000);

        fetch("/api/settime?timestamp=" + unixTimestamp, { method: "GET" })
            .then(response => response.json())
            .then(data => {
                console.log(data);
            })
            .catch(error => {
                console.log("Error sending timestamp:", error);
            });
    } else {
        console.log("Please select a valid date and time.");
    }
});

// Fetch schedule on page load
fetchSchedule();
