from services.base import ServiceBase
from helpers import round_up


class Synchronizer(ServiceBase):
    def update_config(self, agents: int,
                      storage: float,
                      distributed: bool,
                      traffic: float = None,
                      mail_traffic: float = None,
                      nodes: int = None) -> None:
        self._replicas = 1 if agents > 0 else 0
        self._memory = round_up(storage / 5000, 3) * 1.6 if distributed else 100
        self._cpu = 1
        self._storage = round_up(0.0002 * agents + 0.6, 3) if distributed else 0