# AI Usage Log

| AI tool | Prompt / question | How I used and verified the response |
|---|---|---|
| ChatGPT | “Suggest simple categories of academic advice based on a student's CGPA, with understandable threshold bands.” | Used the idea of four bands (excellent, good, needs improvement, immediate attention). I turned them into fixed thresholds in `academicAdvisor` using C `if` / `else if` logic and reviewed that every CGPA from 0 to 10 selects one message. |
| ChatGPT | “Suggest edge cases for averaging SGPA values to calculate CGPA.” | Used the cases of no available values and a mixture of available and missing semesters. In the program, zero represents an unavailable semester, only positive values are averaged, and an empty record returns 0.00. |

The advisor runs entirely in the C program and does not call an AI service. The thresholds and messages are illustrative rules; review them and be prepared to explain or adjust them for course requirements.
