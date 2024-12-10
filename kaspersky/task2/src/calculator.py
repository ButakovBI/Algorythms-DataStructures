from typing import Any, Dict, Type

from services.base import ServiceBase


class Calculator:
    def __init__(self, config: Dict[str, Dict[str, Any]],
                 services: Dict[str, Type[ServiceBase]],
                 parameters: Dict[str, Any]) -> None:
        """
        Инициализирует реестр сервисов и
        регистрирует сервисы на основе конфигурации.
        """
        self._config = config
        self._services: Dict[str, ServiceBase] = {}
        self.register_services(services)
        self._params = parameters
        self.update_all_configs()

    def register_services(
            self, services: Dict[str, Type[ServiceBase]]) -> None:
        """
        Регистрирует сервисы в калькуляторе на основе переданного словаря.

        Args:
            services (Dict[str, Type[ServiceBase]]):
            Словарь с именами сервисов и соответствующими классами.
        """
        for service_name, service_class in services.items():
            if service_name in self._config:
                self.register_service(service_name, service_class())

    def register_service(self, name: str, service: ServiceBase) -> None:
        """
        Регистрирует новый сервис в калькуляторе.

        Args:
            name (str): Имя сервиса (ключ в реестре).
            service (ServiceBase):
            Экземпляр сервиса, реализующий интерфейс ServiceBase.
        """
        self._services[name] = service

    def update_all_configs(self) -> None:
        """
        Обновляет конфигурацию всех зарегистрированных сервисов
        на основе входного конфигурационного словаря.
        """
        for service_name in self._config:
            if service_name in self._services:
                self._services[service_name].update_config(
                    agents=self._params.get("agents"),
                    storage=self._params.get("storage"),
                    traffic=self._params.get("traffic"),
                    mail_traffic=self._params.get("mail_traffic"),
                    distributed=self._params.get("distributed"),
                    nodes=self._params.get("nodes")
                )

    def get_all_configs(self) -> Dict[str, Dict[str, Any]]:
        """
        Возвращает конфигурацию всех сервисов в виде словаря.

        Если сервис из конфигурации отсутствует в зарегистрированных сервисах,
        он также будет добавлен в результат
        с исходными значениями конфигурации.

        Returns:
            Dict[str, Dict[str, Any]]: Словарь с конфигурациями всех сервисов.
        """
        result = {}

        for name, service in self._services.items():
            result[name] = service.get_config()

        for service_name, params in self._config.items():
            if service_name not in self._services:
                result[service_name] = params

        return result
