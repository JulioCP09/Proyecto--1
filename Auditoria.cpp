#include "Auditoria.h"

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

void inicializarAuditoria() {
    std::ofstream archivo("auditoria_log.csv", std::ios::app);
    if (!archivo) std::cerr << "No se pudo crear auditoria_log.csv.\n";
}

void registrarAuditoria(const std::string& idUsuario,
                        const std::string& accion,
                        int idTarea) {
    std::ofstream archivo("auditoria_log.csv", std::ios::app);
    if (!archivo) {
        std::cerr << "No se pudo abrir auditoria_log.csv para escritura.\n";
        return;
    }

    const std::time_t ahora = std::time(nullptr);
    const std::tm* fecha = std::localtime(&ahora);
    if (!fecha) {
        std::cerr << "No se pudo obtener la fecha para la auditoria.\n";
        return;
    }

    archivo << std::put_time(fecha, "%d/%m/%Y %H:%M:%S") << " | "
            << idUsuario << " | " << accion << " | " << idTarea << "\n";
}