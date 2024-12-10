from services.base import ServiceBase
from helpers import round_up


class Kafka(ServiceBase):
    def update_config(self, agents: int,
                      mail_traffic: float,
                      distributed: bool,
                      nodes: int,
                      storage: float = None,
                      traffic: float = None, ) -> None:
        self._replicas = 3 if distributed else 1
        self._memory = mail_traffic * 0.5 if distributed else 100
        self._cpu = round_up((0.000169 * agents + 0.437923) * nodes / 3, 2)
        
        self._storage = round_up(0.0004 * agents + 0.3231, 3)