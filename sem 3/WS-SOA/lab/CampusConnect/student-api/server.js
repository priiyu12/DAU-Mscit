const express = require('express');
const swaggerUi = require('swagger-ui-express');
const YAML = require('yamljs');
const path = require('path');

const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json());

// Load Swagger document
const swaggerDocument = YAML.load(path.join(__dirname, 'swagger.yaml'));
app.use('/api-docs', swaggerUi.serve, swaggerUi.setup(swaggerDocument));

// In-memory data store
let students = [
  { id: 1, name: "Aarav Patel", email: "aarav@example.com", course: "Computer Science", semester: 5 },
  { id: 2, name: "Maria Garcia", email: "maria@example.com", course: "Information Technology", semester: 3 }
];
let nextId = 3;

// Validation helper
const validateStudent = (student) => {
  const errors = [];
  if (!student.name || typeof student.name !== 'string') errors.push("Valid name is required");
  if (!student.email || typeof student.email !== 'string' || !student.email.includes('@')) errors.push("Valid email is required");
  if (!student.course || typeof student.course !== 'string') errors.push("Valid course is required");
  if (student.semester === undefined || typeof student.semester !== 'number' || student.semester < 1) errors.push("Valid positive semester number is required");
  return errors;
};

// GET all students
app.get('/students', (req, res) => {
  res.status(200).json(students);
});

// GET student by ID
app.get('/students/:id', (req, res) => {
  const id = parseInt(req.params.id);
  const student = students.find(s => s.id === id);
  
  if (student) {
    res.status(200).json(student);
  } else {
    res.status(404).json({ error: "Student not found" });
  }
});

// POST a new student
app.post('/students', (req, res) => {
  const errors = validateStudent(req.body);
  if (errors.length > 0) {
    return res.status(400).json({ errors });
  }

  const newStudent = {
    id: nextId++,
    name: req.body.name,
    email: req.body.email,
    course: req.body.course,
    semester: req.body.semester
  };
  
  students.push(newStudent);
  res.status(201).json(newStudent);
});

// PUT (update) a student
app.put('/students/:id', (req, res) => {
  const id = parseInt(req.params.id);
  const studentIndex = students.findIndex(s => s.id === id);
  
  if (studentIndex === -1) {
    return res.status(404).json({ error: "Student not found" });
  }

  const errors = validateStudent(req.body);
  if (errors.length > 0) {
    return res.status(400).json({ errors });
  }

  students[studentIndex] = {
    id, // preserve the existing id
    name: req.body.name,
    email: req.body.email,
    course: req.body.course,
    semester: req.body.semester
  };
  
  res.status(200).json(students[studentIndex]);
});

// PATCH (partial update) a student
app.patch('/students/:id', (req, res) => {
  const id = parseInt(req.params.id);
  const studentIndex = students.findIndex(s => s.id === id);
  
  if (studentIndex === -1) {
    return res.status(404).json({ error: "Student not found" });
  }

  // Partial update, don't validate everything, just what's provided
  const updatedStudent = { ...students[studentIndex] };
  const errors = [];

  if (req.body.name !== undefined) {
    if (typeof req.body.name !== 'string' || req.body.name.trim() === '') errors.push("Valid name is required");
    else updatedStudent.name = req.body.name;
  }
  if (req.body.email !== undefined) {
    if (typeof req.body.email !== 'string' || !req.body.email.includes('@')) errors.push("Valid email is required");
    else updatedStudent.email = req.body.email;
  }
  if (req.body.course !== undefined) {
    if (typeof req.body.course !== 'string' || req.body.course.trim() === '') errors.push("Valid course is required");
    else updatedStudent.course = req.body.course;
  }
  if (req.body.semester !== undefined) {
    if (typeof req.body.semester !== 'number' || req.body.semester < 1) errors.push("Valid positive semester number is required");
    else updatedStudent.semester = req.body.semester;
  }

  if (errors.length > 0) {
    return res.status(400).json({ errors });
  }

  students[studentIndex] = updatedStudent;
  res.status(200).json(updatedStudent);
});

// DELETE a student
app.delete('/students/:id', (req, res) => {
  const id = parseInt(req.params.id);
  const studentIndex = students.findIndex(s => s.id === id);
  
  if (studentIndex === -1) {
    return res.status(404).json({ error: "Student not found" });
  }

  students.splice(studentIndex, 1);
  // Requirement says 204 or 200. We will use 200 with a message or 204. Let's use 204.
  res.status(204).send();
});

// Error handling middleware for unexpected errors
app.use((err, req, res, next) => {
  console.error(err.stack);
  res.status(500).json({ error: "Internal Server Error" });
});

app.listen(PORT, () => {
  console.log(`Express Server running on port ${PORT}`);
  console.log(`Swagger UI available at http://localhost:${PORT}/api-docs`);
});
