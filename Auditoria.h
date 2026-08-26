#ifndef AUDITORIA_H
#define AUDITORIA_H

#include <string>

void inicializarAuditoria();
void registrarAuditoria(const std::string& idUsuario,
                        const std::string& accion,
                        int idTarea);

#endif