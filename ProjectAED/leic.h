#ifndef PROJECTAED_LEIC_H
#define PROJECTAED_LEIC_H
#include <vector>
#include <stack>
#include <map>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "student.h"
#include "request.h"

/**
 * \class LEIC
 * \brief This is a class for the course LEIC.
 *
 * This class keeps track of all of LEIC's Classe, UC's, all Student and respective changes.
 */
class LEIC {
private:
  std::vector<Class> classes;
  std::set<std::string> ucs;
  std::map<std::string, Student> up_students;
  std::queue<Request> requests; //pedidos para serem tratados class request?
  std::stack<Request> processed_requests; //últimos pedidos
  int CAP = 30;
public:
    /**
     * \brief Creates a new LEIC.
     *
     * Reads the files and populates the data in LEIC.
     *
     * @param filenameclasses The file name and location for the Classes file.
     * @param filenamestudents The file name and location for the Students file.
     */
    LEIC(std::string filenameclasses, std::string filenamestudents); //ler ficheiros e guardar info
    /**
    * \brief Gets the Student with the given up.
    *
    * @param up The up of the Student to get.
    * @return Reference to the Student with the given up.
    */
    Student* get_student_from_up(std::string up);
    /**
    * \brief Gets the UC codes of all existing UC.
    *
    * @return The UC codes of all existing UC.
    */
    std::set<std::string> get_ucs() const;
    /**
    * \brief Gets all existing Class in LEIC.
    *
    * @return All existing Class in LEIC.
    */
    std::vector<Class> get_classes() const;
    /**
    * \brief Gets the Class codes of all existing Class.
    *
    * @return The Class codes of all existing Class.
    */
    std::set<std::string> get_classcodes() const;
    /**
    * \brief Sets a new Cap, the max number of Student that can be in a Class.
    *
    * @param cap The value to set the Cap.
    */
    void set_cap(int cap);
    /**
    * \brief Gets the Cap, the max number of Student that can be in a Class.
    *
    * @return The Cap.
    */
    int get_cap();
    /**
    * \brief Prints all of the Student enrolled in the course sorted by their up.
    */
    void listStudentsByUP();
    /**
    * \brief Prints all of the Student enrolled in the course sorted by their name.
    */
    void listStudentsByName();
    /**
     * \brief Prints all of the Student enrolled in the given UC sorted by their up.
     *
     * @param uc The UC code of the UC to print all Student.
     */
    void listUCStudentsByUP(std::string uc);
    /**
     * \brief Prints all of the Student enrolled in the given UC sorted by their name.
     *
     * @param uc The UC code of the UC to print all Student.
     */
    void listUCStudentsByName(std::string uc);
    /**
     * \brief Prints all of the Student enrolled in the given Class sorted by their up.
     *
     * @param class_ The Class to print all Student.
     */
    void list_class_students_by_UP(Class* class_) const;
    /**
     * \brief Prints all of the Student enrolled in the given Class sorted by their name.
     *
     * @param class_ The Class to print all Student.
     */
    void list_class_students_by_Name(Class* class_) const;
    /**
     * \brief Gets the Class with the given Class code and UC code.
     *
     * @param classcode The Class code of the Class to get.
     * @param uccode The UC code of the Class to get.
     * @return Reference to the Class with the given Class code and UC code.
     */
    Class* get_class_from_classcode_and_uccode(std::string classcode, std::string uccode);
    /**
     * \brief Gets all Class with the given UC code.
     *
     * @param uccode The UC code of all Class to get.
     * @return References of all Class with the given UC code.
     */
    std::vector<Class*> get_classes_from_uccode(std::string uccode);
    /**
     * \brief Checks if by inserting a Student into a Class, the Class Balance is valid.
     *
     * @param newClass The Class to insert a Student to check.
     * @return True if by inserting a Student into a Class, the Class Balance is valid.
     */
    bool class_balance_valid(Class newClass);
    /**
     * \brief Checks if a Student schedule can accept all TP or PL Lesson of the given Class,
     *        excluding all of the old Class's Lesson if applicable.
     *
     * @param student The Student to check Schedule compatibility.
     * @param newclass The Class to check Schedule compatibility.
     * @param oldclass The Class to exclude from the Student's Schedule, if applicable.
     * @return True if the Student schedule can accept all TP or PL Lesson of the given Class,
     *        excluding all of the old Class's Lesson if applicable.
     */
    bool compatible_schedules(Student student, Class* newclass, Class* oldclass = nullptr);
    /**
     * \brief Prints all Class and their respective number of Student enrolled.
     */
    void numberstudents_class();
    /**
     * \brief Adds the given Student to the given Class, updating the data accordingly.
     *
     * @param student The Student to enroll in the given Class.
     * @param newclass The Class to enroll the given Student.
     */
    void add_student_to_class(Student* student, Class* newclass);
    /**
     * \brief Adds a new Student to the data.
     *
     * @param student The Student to add.
     */
    void add_student(Student student);
    /**
     * \brief Removes the given Student from the given Class, updating the data accordingly.
     *
     * @param student The Student to remove from the given Class.
     * @param newclass The Class to remove the given Student.
     */
    void remove_student_from_class(Student* student, Class* newclass);
    bool uc_has_vacancy(std::string uccode);
    bool process_requests(Request request);
    bool request_add(Request request, Student* student);
    bool request_remove(Request request, Student* student);
    bool request_switch(Request request, Student* student);
    bool undo_request();
    void save_to_files();
};

#endif