from services.base import ServiceBase
from helpers import round_up


class Scanner(ServiceBase):
    def update_config(self, agents: int,
                      distributed: bool,
                      storage: float = None,
                      traffic: float = None,
                      mail_traffic: float = None,
                      nodes: int = None) -> None:
        self._replicas = 1 if agents > 0 else 0
        self._memory = 300
        self._cpu = 1
        self._storage = round_up(0.0002 * agents + 0.6, 3) if distributed else 0