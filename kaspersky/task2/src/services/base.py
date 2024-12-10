from abc import ABC, abstractmethod
from typing import Dict, Union


class ServiceBase(ABC):
    def __init__(self) -> None:
        """
        Инициализирует базовые параметры сервиса с начальными значениями:
        replicas, memory, cpu, и storage, которые будут настраиваться в наследниках.
        """
        self._replicas: int = 0
        self._memory: Union[int, float] = 0
        self._cpu: int = 0
        self._storage: Union[int, float] = 0

    @abstractmethod
    def update_config(self, **kwargs) -> None:
        """
        Абстрактный метод для обновления параметров сервиса.
        Должен быть реализован в каждом подклассе.
        
        Args:
            kwargs: Параметры, используемые для настройки конфигурации сервиса.
        """
        pass

    def get_config(self) -> Dict[str, Union[int, float]]:
        """
        Возвращает текущую конфигурацию сервиса в виде словаря.

        Returns:
            Dict[str, Union[int, float]]: Словарь с текущими значениями параметров
            replicas, memory, cpu, и storage.
        """
        return {
            "replicas": self._replicas,
            "memory": self._memory,
            "cpu": self._cpu,
            "storage": self._storage
        }